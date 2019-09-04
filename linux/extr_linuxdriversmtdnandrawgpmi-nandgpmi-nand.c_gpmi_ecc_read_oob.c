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
struct nand_chip {int /*<<< orphan*/  (* read_byte ) (struct mtd_info*) ;int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ GPMI_IS_MX23 (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*) ; 

__attribute__((used)) static int gpmi_ecc_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
				int page)
{
	struct gpmi_nand_data *this = nand_get_controller_data(chip);

	dev_dbg(this->dev, "page number is %d\n", page);
	/* clear the OOB buffer */
	memset(chip->oob_poi, ~0, mtd->oobsize);

	/* Read out the conventional OOB. */
	nand_read_page_op(chip, page, mtd->writesize, NULL, 0);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	/*
	 * Now, we want to make sure the block mark is correct. In the
	 * non-transcribing case (!GPMI_IS_MX23()), we already have it.
	 * Otherwise, we need to explicitly read it.
	 */
	if (GPMI_IS_MX23(this)) {
		/* Read the block mark into the first byte of the OOB buffer. */
		nand_read_page_op(chip, page, 0, NULL, 0);
		chip->oob_poi[0] = chip->read_byte(mtd);
	}

	return 0;
}