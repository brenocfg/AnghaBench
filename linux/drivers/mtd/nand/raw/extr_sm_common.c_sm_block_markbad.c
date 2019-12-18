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
struct sm_oob {int block_status; } ;
struct nand_chip {int dummy; } ;
struct mtd_oob_ops {scalar_t__ oobretlen; int /*<<< orphan*/ * datbuf; void* oobbuf; int /*<<< orphan*/  ooblen; scalar_t__ ooboffs; int /*<<< orphan*/  mode; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 scalar_t__ SM_OOB_SIZE ; 
 int /*<<< orphan*/  memset (struct sm_oob*,int,scalar_t__) ; 
 int mtd_write_oob (struct mtd_info*,scalar_t__,struct mtd_oob_ops*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 

__attribute__((used)) static int sm_block_markbad(struct nand_chip *chip, loff_t ofs)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mtd_oob_ops ops;
	struct sm_oob oob;
	int ret;

	memset(&oob, -1, SM_OOB_SIZE);
	oob.block_status = 0x0F;

	/* As long as this function is called on erase block boundaries
		it will work correctly for 256 byte nand */
	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = (void *)&oob;
	ops.datbuf = NULL;


	ret = mtd_write_oob(mtd, ofs, &ops);
	if (ret < 0 || ops.oobretlen != SM_OOB_SIZE) {
		pr_notice("sm_common: can't mark sector at %i as bad\n",
			  (int)ofs);
		return -EIO;
	}

	return 0;
}