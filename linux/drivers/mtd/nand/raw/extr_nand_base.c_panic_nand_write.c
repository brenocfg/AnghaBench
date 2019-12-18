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
struct nand_chip {int chip_shift; } ;
struct mtd_oob_ops {size_t len; size_t retlen; int /*<<< orphan*/  mode; int /*<<< orphan*/ * datbuf; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  ops ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 int /*<<< orphan*/  memset (struct mtd_oob_ops*,int /*<<< orphan*/ ,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_do_write_ops (struct nand_chip*,int,struct mtd_oob_ops*) ; 
 int /*<<< orphan*/  nand_select_target (struct nand_chip*,int) ; 
 int /*<<< orphan*/  panic_nand_wait (struct nand_chip*,int) ; 

__attribute__((used)) static int panic_nand_write(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, const uint8_t *buf)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int chipnr = (int)(to >> chip->chip_shift);
	struct mtd_oob_ops ops;
	int ret;

	nand_select_target(chip, chipnr);

	/* Wait for the device to get ready */
	panic_nand_wait(chip, 400);

	memset(&ops, 0, sizeof(ops));
	ops.len = len;
	ops.datbuf = (uint8_t *)buf;
	ops.mode = MTD_OPS_PLACE_OOB;

	ret = nand_do_write_ops(chip, to, &ops);

	*retlen = ops.retlen;
	return ret;
}