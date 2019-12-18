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
typedef  int u64 ;
struct pblk_line {scalar_t__ cur_sec; int /*<<< orphan*/  map_bitmap; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ sec_per_line; } ;
struct pblk {TYPE_1__ lm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

u64 __pblk_alloc_page(struct pblk *pblk, struct pblk_line *line, int nr_secs)
{
	u64 addr;
	int i;

	lockdep_assert_held(&line->lock);

	/* logic error: ppa out-of-bounds. Prevent generating bad address */
	if (line->cur_sec + nr_secs > pblk->lm.sec_per_line) {
		WARN(1, "pblk: page allocation out of bounds\n");
		nr_secs = pblk->lm.sec_per_line - line->cur_sec;
	}

	line->cur_sec = addr = find_next_zero_bit(line->map_bitmap,
					pblk->lm.sec_per_line, line->cur_sec);
	for (i = 0; i < nr_secs; i++, line->cur_sec++)
		WARN_ON(test_and_set_bit(line->cur_sec, line->map_bitmap));

	return addr;
}