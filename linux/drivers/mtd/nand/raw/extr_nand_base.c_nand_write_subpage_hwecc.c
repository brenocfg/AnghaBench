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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int size; int bytes; int steps; int /*<<< orphan*/  total; int /*<<< orphan*/  const* calc_buf; int /*<<< orphan*/  (* calculate ) (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* hwctl ) (struct nand_chip*,int /*<<< orphan*/ ) ;} ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; TYPE_1__ ecc; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_WRITE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int,int) ; 
 int mtd_ooblayout_set_eccbytes (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int nand_write_data_op (struct nand_chip*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int nand_write_subpage_hwecc(struct nand_chip *chip, uint32_t offset,
				    uint32_t data_len, const uint8_t *buf,
				    int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	uint8_t *oob_buf  = chip->oob_poi;
	uint8_t *ecc_calc = chip->ecc.calc_buf;
	int ecc_size      = chip->ecc.size;
	int ecc_bytes     = chip->ecc.bytes;
	int ecc_steps     = chip->ecc.steps;
	uint32_t start_step = offset / ecc_size;
	uint32_t end_step   = (offset + data_len - 1) / ecc_size;
	int oob_bytes       = mtd->oobsize / ecc_steps;
	int step, ret;

	ret = nand_prog_page_begin_op(chip, page, 0, NULL, 0);
	if (ret)
		return ret;

	for (step = 0; step < ecc_steps; step++) {
		/* configure controller for WRITE access */
		chip->ecc.hwctl(chip, NAND_ECC_WRITE);

		/* write data (untouched subpages already masked by 0xFF) */
		ret = nand_write_data_op(chip, buf, ecc_size, false);
		if (ret)
			return ret;

		/* mask ECC of un-touched subpages by padding 0xFF */
		if ((step < start_step) || (step > end_step))
			memset(ecc_calc, 0xff, ecc_bytes);
		else
			chip->ecc.calculate(chip, buf, ecc_calc);

		/* mask OOB of un-touched subpages by padding 0xFF */
		/* if oob_required, preserve OOB metadata of written subpage */
		if (!oob_required || (step < start_step) || (step > end_step))
			memset(oob_buf, 0xff, oob_bytes);

		buf += ecc_size;
		ecc_calc += ecc_bytes;
		oob_buf  += oob_bytes;
	}

	/* copy calculated ECC for whole page to chip->buffer->oob */
	/* this include masked-value(0xFF) for unwritten subpages */
	ecc_calc = chip->ecc.calc_buf;
	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	if (ret)
		return ret;

	/* write OOB buffer to NAND device */
	ret = nand_write_data_op(chip, chip->oob_poi, mtd->oobsize, false);
	if (ret)
		return ret;

	return nand_prog_page_end_op(chip);
}