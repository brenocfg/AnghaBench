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
struct nand_chip {int badblockpos; int options; } ;
struct mtd_oob_ops {int ooboffs; int len; int ooblen; int /*<<< orphan*/  mode; int /*<<< orphan*/ * oobbuf; } ;
struct mtd_info {int writesize; } ;
typedef  int /*<<< orphan*/  ops ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  memset (struct mtd_oob_ops*,int /*<<< orphan*/ ,int) ; 
 int nand_bbm_get_next_page (struct nand_chip*,int) ; 
 int nand_do_write_oob (struct nand_chip*,scalar_t__,struct mtd_oob_ops*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int nand_default_block_markbad(struct nand_chip *chip, loff_t ofs)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mtd_oob_ops ops;
	uint8_t buf[2] = { 0, 0 };
	int ret = 0, res, page_offset;

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

	page_offset = nand_bbm_get_next_page(chip, 0);

	while (page_offset >= 0) {
		res = nand_do_write_oob(chip,
					ofs + (page_offset * mtd->writesize),
					&ops);

		if (!ret)
			ret = res;

		page_offset = nand_bbm_get_next_page(chip, page_offset + 1);
	}

	return ret;
}