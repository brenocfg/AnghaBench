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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int size; int bytes; int steps; int /*<<< orphan*/  total; int /*<<< orphan*/ * calc_buf; int /*<<< orphan*/  (* hwctl ) (struct mtd_info*,int /*<<< orphan*/ ) ;} ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_WRITE ; 
 int _omap_calculate_ecc_bch (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int mtd_ooblayout_set_eccbytes (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_write_subpage_bch(struct mtd_info *mtd,
				  struct nand_chip *chip, u32 offset,
				  u32 data_len, const u8 *buf,
				  int oob_required, int page)
{
	u8 *ecc_calc = chip->ecc.calc_buf;
	int ecc_size      = chip->ecc.size;
	int ecc_bytes     = chip->ecc.bytes;
	int ecc_steps     = chip->ecc.steps;
	u32 start_step = offset / ecc_size;
	u32 end_step   = (offset + data_len - 1) / ecc_size;
	int step, ret = 0;

	/*
	 * Write entire page at one go as it would be optimal
	 * as ECC is calculated by hardware.
	 * ECC is calculated for all subpages but we choose
	 * only what we want.
	 */
	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	/* Enable GPMC ECC engine */
	chip->ecc.hwctl(mtd, NAND_ECC_WRITE);

	/* Write data */
	chip->write_buf(mtd, buf, mtd->writesize);

	for (step = 0; step < ecc_steps; step++) {
		/* mask ECC of un-touched subpages by padding 0xFF */
		if (step < start_step || step > end_step)
			memset(ecc_calc, 0xff, ecc_bytes);
		else
			ret = _omap_calculate_ecc_bch(mtd, buf, ecc_calc, step);

		if (ret)
			return ret;

		buf += ecc_size;
		ecc_calc += ecc_bytes;
	}

	/* copy calculated ECC for whole page to chip->buffer->oob */
	/* this include masked-value(0xFF) for unwritten subpages */
	ecc_calc = chip->ecc.calc_buf;
	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	if (ret)
		return ret;

	/* write OOB buffer to NAND device */
	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return nand_prog_page_end_op(chip);
}