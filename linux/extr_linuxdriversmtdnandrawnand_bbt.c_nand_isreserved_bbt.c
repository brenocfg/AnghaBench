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
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ BBT_BLOCK_RESERVED ; 
 scalar_t__ bbt_get_entry (struct nand_chip*,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

int nand_isreserved_bbt(struct mtd_info *mtd, loff_t offs)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	int block;

	block = (int)(offs >> this->bbt_erase_shift);
	return bbt_get_entry(this, block) == BBT_BLOCK_RESERVED;
}