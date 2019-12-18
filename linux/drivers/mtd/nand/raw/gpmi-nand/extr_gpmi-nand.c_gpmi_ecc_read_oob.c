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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int oobsize; int /*<<< orphan*/  writesize; } ;
struct gpmi_nand_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPMI_IS_MX23 (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_ecc_read_oob(struct nand_chip *chip, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	int ret;

	/* clear the OOB buffer */
	memset(chip->oob_poi, ~0, mtd->oobsize);

	/* Read out the conventional OOB. */
	ret = nand_read_page_op(chip, page, mtd->writesize, chip->oob_poi,
				mtd->oobsize);
	if (ret)
		return ret;

	/*
	 * Now, we want to make sure the block mark is correct. In the
	 * non-transcribing case (!GPMI_IS_MX23()), we already have it.
	 * Otherwise, we need to explicitly read it.
	 */
	if (GPMI_IS_MX23(this)) {
		/* Read the block mark into the first byte of the OOB buffer. */
		ret = nand_read_page_op(chip, page, 0, chip->oob_poi, 1);
		if (ret)
			return ret;
	}

	return 0;
}