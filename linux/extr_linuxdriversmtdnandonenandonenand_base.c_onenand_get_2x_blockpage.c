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
struct onenand_chip {int erase_shift; int writesize; int page_shift; int page_mask; } ;
struct mtd_info {struct onenand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */

__attribute__((used)) static int onenand_get_2x_blockpage(struct mtd_info *mtd, loff_t addr)
{
	struct onenand_chip *this = mtd->priv;
	int blockpage, block, page;

	/* Calculate the even block number */
	block = (int) (addr >> this->erase_shift) & ~1;
	/* Is it the odd plane? */
	if (addr & this->writesize)
		block++;
	page = (int) (addr >> (this->page_shift + 1)) & this->page_mask;
	blockpage = (block << 7) | page;

	return blockpage;
}