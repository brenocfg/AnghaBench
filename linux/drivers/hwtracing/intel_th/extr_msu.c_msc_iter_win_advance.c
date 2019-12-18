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
struct msc_iter {scalar_t__ win; scalar_t__ start_win; int /*<<< orphan*/  eof; int /*<<< orphan*/ * start_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  msc_iter_block_start (struct msc_iter*) ; 
 scalar_t__ msc_next_window (scalar_t__) ; 

__attribute__((used)) static int msc_iter_win_advance(struct msc_iter *iter)
{
	iter->win = msc_next_window(iter->win);
	iter->start_block = NULL;

	if (iter->win == iter->start_win) {
		iter->eof++;
		return 1;
	}

	msc_iter_block_start(iter);

	return 0;
}