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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int badblockpos; int options; int bbt_options; } ;
struct mtd_oob_ops {int ooboffs; int len; int ooblen; int /*<<< orphan*/  mode; int /*<<< orphan*/ * oobbuf; } ;
struct mtd_info {scalar_t__ writesize; scalar_t__ erasesize; } ;
typedef  int /*<<< orphan*/  ops ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 int NAND_BBT_SCAN2NDPAGE ; 
 int NAND_BBT_SCANLASTPAGE ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  memset (struct mtd_oob_ops*,int /*<<< orphan*/ ,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_do_write_oob (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int nand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtd_oob_ops ops;
	uint8_t buf[2] = { 0, 0 };
	int ret = 0, res, i = 0;

	memset(&ops, 0, sizeof(ops));
	ops.oobbuf = buf;
	ops.ooboffs = chip->badblockpos;
	if (chip->options & NAND_BUSWIDTH_16) {
		ops.ooboffs &= ~0x01;
		ops.len = ops.ooblen = 2;
	} else {
		ops.len = ops.ooblen = 1;
	}
	ops.mode = MTD_OPS_PLACE_OOB;

	/* Write to first/last page(s) if necessary */
	if (chip->bbt_options & NAND_BBT_SCANLASTPAGE)
		ofs += mtd->erasesize - mtd->writesize;
	do {
		res = nand_do_write_oob(mtd, ofs, &ops);
		if (!ret)
			ret = res;

		i++;
		ofs += mtd->writesize;
	} while ((chip->bbt_options & NAND_BBT_SCAN2NDPAGE) && i < 2);

	return ret;
}