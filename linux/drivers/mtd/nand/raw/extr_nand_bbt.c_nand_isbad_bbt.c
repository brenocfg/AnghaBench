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
struct nand_chip {int bbt_erase_shift; } ;
typedef  int loff_t ;

/* Variables and functions */
#define  BBT_BLOCK_GOOD 130 
#define  BBT_BLOCK_RESERVED 129 
#define  BBT_BLOCK_WORN 128 
 int bbt_get_entry (struct nand_chip*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int,int) ; 

int nand_isbad_bbt(struct nand_chip *this, loff_t offs, int allowbbt)
{
	int block, res;

	block = (int)(offs >> this->bbt_erase_shift);
	res = bbt_get_entry(this, block);

	pr_debug("nand_isbad_bbt(): bbt info for offs 0x%08x: (block %d) 0x%02x\n",
		 (unsigned int)offs, block, res);

	switch (res) {
	case BBT_BLOCK_GOOD:
		return 0;
	case BBT_BLOCK_WORN:
		return 1;
	case BBT_BLOCK_RESERVED:
		return allowbbt ? 0 : 1;
	}
	return 1;
}