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
struct msc_iter {int /*<<< orphan*/ * start_block; scalar_t__ start_win; scalar_t__ win; } ;
struct msc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  msc_iter_block_start (struct msc_iter*) ; 
 scalar_t__ msc_oldest_window (struct msc*) ; 

__attribute__((used)) static int msc_iter_win_start(struct msc_iter *iter, struct msc *msc)
{
	/* already started, nothing to do */
	if (iter->start_win)
		return 0;

	iter->start_win = msc_oldest_window(msc);
	if (!iter->start_win)
		return -EINVAL;

	iter->win = iter->start_win;
	iter->start_block = NULL;

	msc_iter_block_start(iter);

	return 0;
}