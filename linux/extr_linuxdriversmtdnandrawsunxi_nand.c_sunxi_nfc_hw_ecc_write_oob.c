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
struct TYPE_2__ {int (* write_page ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ;} ;
struct nand_chip {int pagebuf; int /*<<< orphan*/  data_buf; TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int stub1 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_write_oob(struct mtd_info *mtd,
				      struct nand_chip *chip,
				      int page)
{
	int ret;

	chip->pagebuf = -1;

	memset(chip->data_buf, 0xff, mtd->writesize);
	ret = chip->ecc.write_page(mtd, chip, chip->data_buf, 1, page);
	if (ret)
		return ret;

	/* Send command to program the OOB data */
	return nand_prog_page_end_op(chip);
}