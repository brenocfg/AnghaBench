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
struct TYPE_4__ {int /*<<< orphan*/  (* write_buf ) (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  steps; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; TYPE_2__ legacy; TYPE_1__ ecc; } ;
struct mtd_oob_region {int offset; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
struct lpc32xx_nand_host {scalar_t__ ecc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpc32xx_slc_ecc_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lpc32xx_xfer (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_nand_write_page_syndrome(struct nand_chip *chip,
					    const uint8_t *buf,
					    int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	struct mtd_oob_region oobregion = { };
	uint8_t *pb;
	int error;

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	/* Write data, calculate ECC on outbound data */
	error = lpc32xx_xfer(mtd, (uint8_t *)buf, chip->ecc.steps, 0);
	if (error)
		return error;

	/*
	 * The calculated ECC needs some manual work done to it before
	 * committing it to NAND. Process the calculated ECC and place
	 * the resultant values directly into the OOB buffer. */
	error = mtd_ooblayout_ecc(mtd, 0, &oobregion);
	if (error)
		return error;

	pb = chip->oob_poi + oobregion.offset;
	lpc32xx_slc_ecc_copy(pb, (uint32_t *)host->ecc_buf, chip->ecc.steps);

	/* Write ECC data to device */
	chip->legacy.write_buf(chip, chip->oob_poi, mtd->oobsize);

	return nand_prog_page_end_op(chip);
}