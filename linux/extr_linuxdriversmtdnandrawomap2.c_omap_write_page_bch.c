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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  total; int /*<<< orphan*/  (* hwctl ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * calc_buf; } ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_WRITE ; 
 int mtd_ooblayout_set_eccbytes (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int /*<<< orphan*/  omap_calculate_ecc_bch_multi (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_write_page_bch(struct mtd_info *mtd, struct nand_chip *chip,
			       const uint8_t *buf, int oob_required, int page)
{
	int ret;
	uint8_t *ecc_calc = chip->ecc.calc_buf;

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	/* Enable GPMC ecc engine */
	chip->ecc.hwctl(mtd, NAND_ECC_WRITE);

	/* Write data */
	chip->write_buf(mtd, buf, mtd->writesize);

	/* Update ecc vector from GPMC result registers */
	omap_calculate_ecc_bch_multi(mtd, buf, &ecc_calc[0]);

	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	if (ret)
		return ret;

	/* Write ecc vector to OOB area */
	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return nand_prog_page_end_op(chip);
}