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
struct msc_iter {scalar_t__ block; scalar_t__ start_block; scalar_t__ wrap_count; int /*<<< orphan*/  win; scalar_t__ block_off; } ;

/* Variables and functions */
 scalar_t__ msc_block_last_written (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msc_iter_bdesc (struct msc_iter*) ; 
 int msc_iter_win_advance (struct msc_iter*) ; 
 scalar_t__ msc_win_base_sg (int /*<<< orphan*/ ) ; 
 scalar_t__ sg_is_last (scalar_t__) ; 
 scalar_t__ sg_next (scalar_t__) ; 

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
	if (sg_is_last(iter->block))
		iter->block = msc_win_base_sg(iter->win);
	else
		iter->block = sg_next(iter->block);

	/* no wrapping, sanity check in case there is no last written block */
	if (!iter->wrap_count && iter->block == iter->start_block)
		return msc_iter_win_advance(iter);

	return 0;
}