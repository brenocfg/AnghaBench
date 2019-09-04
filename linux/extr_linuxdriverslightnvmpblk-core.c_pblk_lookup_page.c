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
typedef  int /*<<< orphan*/  u64 ;
struct pblk_line {int /*<<< orphan*/  lock; int /*<<< orphan*/  cur_sec; int /*<<< orphan*/  map_bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  sec_per_line; } ;
struct pblk {TYPE_1__ lm; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

u64 pblk_lookup_page(struct pblk *pblk, struct pblk_line *line)
{
	u64 paddr;

	spin_lock(&line->lock);
	paddr = find_next_zero_bit(line->map_bitmap,
					pblk->lm.sec_per_line, line->cur_sec);
	spin_unlock(&line->lock);

	return paddr;
}