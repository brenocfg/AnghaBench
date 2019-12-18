#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msc_iter {scalar_t__ block; scalar_t__ start_block; int wrap_count; size_t offset; scalar_t__ block_off; scalar_t__ eof; struct msc* msc; } ;
struct msc {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned long DATA_IN_PAGE ; 
 int MSC_BDESC ; 
 unsigned long msc_data_sz (scalar_t__) ; 
 scalar_t__ msc_iter_bdesc (struct msc_iter*) ; 
 scalar_t__ msc_iter_block_advance (struct msc_iter*) ; 
 scalar_t__ msc_iter_win_start (struct msc_iter*,struct msc*) ; 

__attribute__((used)) static ssize_t
msc_buffer_iterate(struct msc_iter *iter, size_t size, void *data,
		   unsigned long (*fn)(void *, void *, size_t))
{
	struct msc *msc = iter->msc;
	size_t len = size;
	unsigned int advance;

	if (iter->eof)
		return 0;

	/* start with the oldest window */
	if (msc_iter_win_start(iter, msc))
		return 0;

	do {
		unsigned long data_bytes = msc_data_sz(msc_iter_bdesc(iter));
		void *src = (void *)msc_iter_bdesc(iter) + MSC_BDESC;
		size_t tocopy = data_bytes, copied = 0;
		size_t remaining = 0;

		advance = 1;

		/*
		 * If block wrapping happened, we need to visit the last block
		 * twice, because it contains both the oldest and the newest
		 * data in this window.
		 *
		 * First time (wrap_count==2), in the very beginning, to collect
		 * the oldest data, which is in the range
		 * (data_bytes..DATA_IN_PAGE).
		 *
		 * Second time (wrap_count==1), it's just like any other block,
		 * containing data in the range of [MSC_BDESC..data_bytes].
		 */
		if (iter->block == iter->start_block && iter->wrap_count == 2) {
			tocopy = DATA_IN_PAGE - data_bytes;
			src += data_bytes;
		}

		if (!tocopy)
			goto next_block;

		tocopy -= iter->block_off;
		src += iter->block_off;

		if (len < tocopy) {
			tocopy = len;
			advance = 0;
		}

		remaining = fn(data, src, tocopy);

		if (remaining)
			advance = 0;

		copied = tocopy - remaining;
		len -= copied;
		iter->block_off += copied;
		iter->offset += copied;

		if (!advance)
			break;

next_block:
		if (msc_iter_block_advance(iter))
			break;

	} while (len);

	return size - len;
}