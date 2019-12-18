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
typedef  int u8 ;
struct TYPE_2__ {int (* read_oob ) (struct nand_chip*,int) ;} ;
struct nand_chip {int page_shift; int pagemask; int* oob_poi; size_t badblockpos; int badblockbits; TYPE_1__ ecc; } ;
typedef  int loff_t ;

/* Variables and functions */
 int hweight8 (int) ; 
 scalar_t__ likely (int) ; 
 int nand_bbm_get_next_page (struct nand_chip*,int) ; 
 int stub1 (struct nand_chip*,int) ; 

__attribute__((used)) static int nand_block_bad(struct nand_chip *chip, loff_t ofs)
{
	int first_page, page_offset;
	int res;
	u8 bad;

	first_page = (int)(ofs >> chip->page_shift) & chip->pagemask;
	page_offset = nand_bbm_get_next_page(chip, 0);

	while (page_offset >= 0) {
		res = chip->ecc.read_oob(chip, first_page + page_offset);
		if (res < 0)
			return res;

		bad = chip->oob_poi[chip->badblockpos];

		if (likely(chip->badblockbits == 8))
			res = bad != 0xFF;
		else
			res = hweight8(bad) < chip->badblockbits;
		if (res)
			return res;

		page_offset = nand_bbm_get_next_page(chip, page_offset + 1);
	}

	return 0;
}