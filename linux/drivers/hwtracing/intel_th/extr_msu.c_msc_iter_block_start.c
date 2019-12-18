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
struct msc_iter {int wrap_count; scalar_t__ start_block; scalar_t__ block; int /*<<< orphan*/  win; } ;

/* Variables and functions */
 scalar_t__ msc_block_wrapped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msc_iter_bdesc (struct msc_iter*) ; 
 scalar_t__ msc_win_oldest_sg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msc_iter_block_start(struct msc_iter *iter)
{
	if (iter->start_block)
		return;

	iter->start_block = msc_win_oldest_sg(iter->win);
	iter->block = iter->start_block;
	iter->wrap_count = 0;

	/*
	 * start with the block with oldest data; if data has wrapped
	 * in this window, it should be in this block
	 */
	if (msc_block_wrapped(msc_iter_bdesc(iter)))
		iter->wrap_count = 2;

}