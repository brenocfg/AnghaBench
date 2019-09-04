#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int steps; int (* correct ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int bytes; int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_2__ ecc; int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct mtd_oob_region {int offset; } ;
struct TYPE_3__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_1__ ecc_stats; int /*<<< orphan*/  oobsize; } ;
struct lpc32xx_nand_host {scalar_t__ ecc_buf; } ;

/* Variables and functions */
 int LPC32XX_ECC_SAVE_SIZE ; 
 int /*<<< orphan*/  lpc32xx_slc_ecc_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int lpc32xx_xfer (struct mtd_info*,int /*<<< orphan*/ *,int,int) ; 
 int mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_nand_read_page_syndrome(struct mtd_info *mtd,
					   struct nand_chip *chip, uint8_t *buf,
					   int oob_required, int page)
{
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	struct mtd_oob_region oobregion = { };
	int stat, i, status, error;
	uint8_t *oobecc, tmpecc[LPC32XX_ECC_SAVE_SIZE];

	/* Issue read command */
	nand_read_page_op(chip, page, 0, NULL, 0);

	/* Read data and oob, calculate ECC */
	status = lpc32xx_xfer(mtd, buf, chip->ecc.steps, 1);

	/* Get OOB data */
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	/* Convert to stored ECC format */
	lpc32xx_slc_ecc_copy(tmpecc, (uint32_t *) host->ecc_buf, chip->ecc.steps);

	/* Pointer to ECC data retrieved from NAND spare area */
	error = mtd_ooblayout_ecc(mtd, 0, &oobregion);
	if (error)
		return error;

	oobecc = chip->oob_poi + oobregion.offset;

	for (i = 0; i < chip->ecc.steps; i++) {
		stat = chip->ecc.correct(mtd, buf, oobecc,
					 &tmpecc[i * chip->ecc.bytes]);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;

		buf += chip->ecc.size;
		oobecc += chip->ecc.bytes;
	}

	return status;
}