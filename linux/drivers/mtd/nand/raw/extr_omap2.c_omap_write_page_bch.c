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
struct TYPE_4__ {int /*<<< orphan*/  (* write_buf ) (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  total; int /*<<< orphan*/  (* hwctl ) (struct nand_chip*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * calc_buf; } ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; TYPE_2__ legacy; TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_WRITE ; 
 int mtd_ooblayout_set_eccbytes (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  omap_calculate_ecc_bch_multi (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_write_page_bch(struct nand_chip *chip, const uint8_t *buf,
			       int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;
	uint8_t *ecc_calc = chip->ecc.calc_buf;

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	/* Enable GPMC ecc engine */
	chip->ecc.hwctl(chip, NAND_ECC_WRITE);

	/* Write data */
	chip->legacy.write_buf(chip, buf, mtd->writesize);

	/* Update ecc vector from GPMC result registers */
	omap_calculate_ecc_bch_multi(mtd, buf, &ecc_calc[0]);

	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	if (ret)
		return ret;

	/* Write ecc vector to OOB area */
	chip->legacy.write_buf(chip, chip->oob_poi, mtd->oobsize);

	return nand_prog_page_end_op(chip);
}