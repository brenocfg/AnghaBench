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
 scalar_t__ BBT_BLOCK_RESERVED ; 
 scalar_t__ bbt_get_entry (struct nand_chip*,int) ; 

int nand_isreserved_bbt(struct nand_chip *this, loff_t offs)
{
	int block;

	block = (int)(offs >> this->bbt_erase_shift);
	return bbt_get_entry(this, block) == BBT_BLOCK_RESERVED;
}