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
struct TYPE_2__ {int (* read_oob ) (struct mtd_info*,struct nand_chip*,int) ;} ;
struct nand_chip {int bbt_options; int page_shift; int pagemask; int* oob_poi; size_t badblockpos; int badblockbits; TYPE_1__ ecc; } ;
struct mtd_info {scalar_t__ writesize; scalar_t__ erasesize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int NAND_BBT_SCAN2NDPAGE ; 
 int NAND_BBT_SCANLASTPAGE ; 
 int hweight8 (int) ; 
 scalar_t__ likely (int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int stub1 (struct mtd_info*,struct nand_chip*,int) ; 

__attribute__((used)) static int nand_block_bad(struct mtd_info *mtd, loff_t ofs)
{
	int page, page_end, res;
	struct nand_chip *chip = mtd_to_nand(mtd);
	u8 bad;

	if (chip->bbt_options & NAND_BBT_SCANLASTPAGE)
		ofs += mtd->erasesize - mtd->writesize;

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;
	page_end = page + (chip->bbt_options & NAND_BBT_SCAN2NDPAGE ? 2 : 1);

	for (; page < page_end; page++) {
		res = chip->ecc.read_oob(mtd, chip, page);
		if (res < 0)
			return res;

		bad = chip->oob_poi[chip->badblockpos];

		if (likely(chip->badblockbits == 8))
			res = bad != 0xFF;
		else
			res = hweight8(bad) < chip->badblockbits;
		if (res)
			return res;
	}

	return 0;
}