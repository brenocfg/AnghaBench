#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msc_iter {scalar_t__ block; scalar_t__ start_block; scalar_t__ wrap_count; TYPE_1__* win; scalar_t__ block_off; } ;
struct TYPE_2__ {scalar_t__ nr_blocks; } ;

/* Variables and functions */
 scalar_t__ msc_block_last_written (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msc_iter_bdesc (struct msc_iter*) ; 
 int msc_iter_win_advance (struct msc_iter*) ; 

__attribute__((used)) static int msc_iter_block_advance(struct msc_iter *iter)
{
	iter->block_off = 0;

	/* wrapping */
	if (iter->wrap_count && iter->block == iter->start_block) {
		iter->wrap_count--;
		if (!iter->wrap_count)
			/* copied newest data from the wrapped block */
			return msc_iter_win_advance(iter);
	}

	/* no wrapping, check for last written block */
	if (!iter->wrap_count && msc_block_last_written(msc_iter_bdesc(iter)))
		/* copied newest data for the window */
		return msc_iter_win_advance(iter);

	/* block advance */
	if (++iter->block == iter->win->nr_blocks)
		iter->block = 0;

	/* no wrapping, sanity check in case there is no last written block */
	if (!iter->wrap_count && iter->block == iter->start_block)
		return msc_iter_win_advance(iter);

	return 0;
}