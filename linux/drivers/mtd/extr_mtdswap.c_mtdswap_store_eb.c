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
struct swap_eb {unsigned int active_count; int flags; } ;
struct mtdswap_dev {unsigned int pages_per_eblk; struct swap_eb* curr_write; } ;

/* Variables and functions */
 int EBLOCK_BITFLIP ; 
 int EBLOCK_FAILED ; 
 int EBLOCK_READERR ; 
 int /*<<< orphan*/  MTDSWAP_BITFLIP ; 
 int /*<<< orphan*/  MTDSWAP_DIRTY ; 
 int /*<<< orphan*/  MTDSWAP_FAILING ; 
 int /*<<< orphan*/  MTDSWAP_HIFRAG ; 
 int /*<<< orphan*/  MTDSWAP_LOWFRAG ; 
 int /*<<< orphan*/  MTDSWAP_USED ; 
 int /*<<< orphan*/  mtdswap_rb_add (struct mtdswap_dev*,struct swap_eb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtdswap_store_eb(struct mtdswap_dev *d, struct swap_eb *eb)
{
	unsigned int weight = eb->active_count;
	unsigned int maxweight = d->pages_per_eblk;

	if (eb == d->curr_write)
		return;

	if (eb->flags & EBLOCK_BITFLIP)
		mtdswap_rb_add(d, eb, MTDSWAP_BITFLIP);
	else if (eb->flags & (EBLOCK_READERR | EBLOCK_FAILED))
		mtdswap_rb_add(d, eb, MTDSWAP_FAILING);
	if (weight == maxweight)
		mtdswap_rb_add(d, eb, MTDSWAP_USED);
	else if (weight == 0)
		mtdswap_rb_add(d, eb, MTDSWAP_DIRTY);
	else if (weight > (maxweight/2))
		mtdswap_rb_add(d, eb, MTDSWAP_LOWFRAG);
	else
		mtdswap_rb_add(d, eb, MTDSWAP_HIFRAG);
}