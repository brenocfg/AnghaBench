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
struct nand_chip {int bbt_options; unsigned long long phys_erase_shift; scalar_t__ bbt; } ;
struct TYPE_2__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {TYPE_1__ ecc_stats; } ;
struct erase_info {unsigned long long len; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  einfo ;

/* Variables and functions */
 int NAND_BBT_NO_OOB_BBM ; 
 int /*<<< orphan*/  memset (struct erase_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nand_erase_nand (struct nand_chip*,struct erase_info*,int /*<<< orphan*/ ) ; 
 int nand_get_device (struct nand_chip*) ; 
 int nand_markbad_bbm (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int nand_markbad_bbt (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release_device (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int nand_block_markbad_lowlevel(struct nand_chip *chip, loff_t ofs)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int res, ret = 0;

	if (!(chip->bbt_options & NAND_BBT_NO_OOB_BBM)) {
		struct erase_info einfo;

		/* Attempt erase before marking OOB */
		memset(&einfo, 0, sizeof(einfo));
		einfo.addr = ofs;
		einfo.len = 1ULL << chip->phys_erase_shift;
		nand_erase_nand(chip, &einfo, 0);

		/* Write bad block marker to OOB */
		ret = nand_get_device(chip);
		if (ret)
			return ret;

		ret = nand_markbad_bbm(chip, ofs);
		nand_release_device(chip);
	}

	/* Mark block bad in BBT */
	if (chip->bbt) {
		res = nand_markbad_bbt(chip, ofs);
		if (!ret)
			ret = res;
	}

	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}