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
typedef  int u64 ;
struct nand_chip {int bbt_erase_shift; int page_shift; int /*<<< orphan*/  base; } ;
struct nand_bbt_descr {int* pages; int options; int maxblocks; } ;

/* Variables and functions */
#define  BBT_BLOCK_FACTORY_BAD 129 
#define  BBT_BLOCK_WORN 128 
 int ENOSPC ; 
 int NAND_BBT_LASTBLOCK ; 
 int NAND_BBT_PERCHIP ; 
 int bbt_get_entry (struct nand_chip*,int) ; 
 int nanddev_ntargets (int /*<<< orphan*/ *) ; 
 int nanddev_target_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_bbt_block(struct nand_chip *this, struct nand_bbt_descr *td,
			 struct nand_bbt_descr *md, int chip)
{
	u64 targetsize = nanddev_target_size(&this->base);
	int startblock, dir, page, numblocks, i;

	/*
	 * There was already a version of the table, reuse the page. This
	 * applies for absolute placement too, as we have the page number in
	 * td->pages.
	 */
	if (td->pages[chip] != -1)
		return td->pages[chip] >>
				(this->bbt_erase_shift - this->page_shift);

	numblocks = (int)(targetsize >> this->bbt_erase_shift);
	if (!(td->options & NAND_BBT_PERCHIP))
		numblocks *= nanddev_ntargets(&this->base);

	/*
	 * Automatic placement of the bad block table. Search direction
	 * top -> down?
	 */
	if (td->options & NAND_BBT_LASTBLOCK) {
		startblock = numblocks * (chip + 1) - 1;
		dir = -1;
	} else {
		startblock = chip * numblocks;
		dir = 1;
	}

	for (i = 0; i < td->maxblocks; i++) {
		int block = startblock + dir * i;

		/* Check, if the block is bad */
		switch (bbt_get_entry(this, block)) {
		case BBT_BLOCK_WORN:
		case BBT_BLOCK_FACTORY_BAD:
			continue;
		}

		page = block << (this->bbt_erase_shift - this->page_shift);

		/* Check, if the block is used by the mirror table */
		if (!md || md->pages[chip] != page)
			return block;
	}

	return -ENOSPC;
}