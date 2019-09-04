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
struct nand_chip {int bbt_options; unsigned long long phys_erase_shift; int (* block_markbad ) (struct mtd_info*,int /*<<< orphan*/ ) ;scalar_t__ bbt; } ;
struct TYPE_2__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {TYPE_1__ ecc_stats; } ;
struct erase_info {unsigned long long len; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  einfo ;

/* Variables and functions */
 int /*<<< orphan*/  FL_WRITING ; 
 int NAND_BBT_NO_OOB_BBM ; 
 int /*<<< orphan*/  memset (struct erase_info*,int /*<<< orphan*/ ,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_erase_nand (struct mtd_info*,struct erase_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int nand_markbad_bbt (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release_device (struct mtd_info*) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_block_markbad_lowlevel(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int res, ret = 0;

	if (!(chip->bbt_options & NAND_BBT_NO_OOB_BBM)) {
		struct erase_info einfo;

		/* Attempt erase before marking OOB */
		memset(&einfo, 0, sizeof(einfo));
		einfo.addr = ofs;
		einfo.len = 1ULL << chip->phys_erase_shift;
		nand_erase_nand(mtd, &einfo, 0);

		/* Write bad block marker to OOB */
		nand_get_device(mtd, FL_WRITING);
		ret = chip->block_markbad(mtd, ofs);
		nand_release_device(mtd);
	}

	/* Mark block bad in BBT */
	if (chip->bbt) {
		res = nand_markbad_bbt(mtd, ofs);
		if (!ret)
			ret = res;
	}

	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}