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
struct swap_eb {int dummy; } ;
struct mtdswap_dev {int pages_per_eblk; scalar_t__ spare_eblks; scalar_t__* revmap; struct swap_eb* eb_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ MIN_SPARE_EBLOCKS ; 
 scalar_t__ PAGE_UNDEF ; 
 int mtdswap_move_block (struct mtdswap_dev*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int mtdswap_gc_eblock(struct mtdswap_dev *d, struct swap_eb *eb)
{
	unsigned int i, block, eblk_base, newblock;
	int ret, errcode;

	errcode = 0;
	eblk_base = (eb - d->eb_data) * d->pages_per_eblk;

	for (i = 0; i < d->pages_per_eblk; i++) {
		if (d->spare_eblks < MIN_SPARE_EBLOCKS)
			return -ENOSPC;

		block = eblk_base + i;
		if (d->revmap[block] == PAGE_UNDEF)
			continue;

		ret = mtdswap_move_block(d, block, &newblock);
		if (ret < 0 && !errcode)
			errcode = ret;
	}

	return errcode;
}