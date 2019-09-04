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
struct msc_window {unsigned int nr_blocks; TYPE_1__* block; } ;
struct msc_block_desc {int dummy; } ;
struct TYPE_2__ {struct msc_block_desc* bdesc; } ;

/* Variables and functions */
 scalar_t__ msc_block_last_written (struct msc_block_desc*) ; 
 int /*<<< orphan*/  msc_block_wrapped (struct msc_block_desc*) ; 

__attribute__((used)) static unsigned int msc_win_oldest_block(struct msc_window *win)
{
	unsigned int blk;
	struct msc_block_desc *bdesc = win->block[0].bdesc;

	/* without wrapping, first block is the oldest */
	if (!msc_block_wrapped(bdesc))
		return 0;

	/*
	 * with wrapping, last written block contains both the newest and the
	 * oldest data for this window.
	 */
	for (blk = 0; blk < win->nr_blocks; blk++) {
		bdesc = win->block[blk].bdesc;

		if (msc_block_last_written(bdesc))
			return blk;
	}

	return 0;
}