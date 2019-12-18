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
struct nand_chip {int bbt_erase_shift; int bbt_options; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBT_BLOCK_WORN ; 
 int NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  bbt_mark_entry (struct nand_chip*,int,int /*<<< orphan*/ ) ; 
 int nand_update_bbt (struct nand_chip*,int) ; 

int nand_markbad_bbt(struct nand_chip *this, loff_t offs)
{
	int block, ret = 0;

	block = (int)(offs >> this->bbt_erase_shift);

	/* Mark bad block in memory */
	bbt_mark_entry(this, block, BBT_BLOCK_WORN);

	/* Update flash-based bad block table */
	if (this->bbt_options & NAND_BBT_USE_FLASH)
		ret = nand_update_bbt(this, offs);

	return ret;
}