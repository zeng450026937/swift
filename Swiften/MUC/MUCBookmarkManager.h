/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/signals.hpp>
#include <boost/optional.hpp>

#include "Swiften/MUC/MUCBookmark.h"
#include "Swiften/Elements/Storage.h"
#include "Swiften/Elements/ErrorPayload.h"

namespace Swift {
	class IQRouter;

	class MUCBookmarkManager {
		public:
			MUCBookmarkManager(IQRouter* iqRouter);

			void addBookmark(const MUCBookmark& bookmark);
			void removeBookmark(const MUCBookmark& bookmark);
			void replaceBookmark(const MUCBookmark& oldBookmark, const MUCBookmark& newBookmark);

			const std::vector<MUCBookmark>& getBookmarks() const; 

		public:
			boost::signal<void (const MUCBookmark&)> onBookmarkAdded;
			boost::signal<void (const MUCBookmark&)> onBookmarkRemoved;

		private:
			bool containsEquivalent(const std::vector<MUCBookmark>& list, const MUCBookmark& bookmark);
			void handleBookmarksReceived(boost::shared_ptr<Storage> payload, const boost::optional<ErrorPayload>& error);
			void flush();

		private:
			std::vector<MUCBookmark> bookmarks_;
			IQRouter* iqRouter_;
			boost::shared_ptr<Storage> storage;
	};
}
