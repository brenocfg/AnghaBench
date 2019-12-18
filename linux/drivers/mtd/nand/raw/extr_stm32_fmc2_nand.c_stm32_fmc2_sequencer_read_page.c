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
typedef  int /*<<< orphan*/  u16 ;
struct stm32_fmc2_nfc {int dummy; } ;
struct TYPE_2__ {int (* correct ) (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  total; int /*<<< orphan*/ * code_buf; int /*<<< orphan*/ * calc_buf; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  oob_poi; int /*<<< orphan*/  cur_cs; int /*<<< orphan*/  controller; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int mtd_ooblayout_get_eccbytes (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nand_change_read_column_op (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stm32_fmc2_get_mapping_status (struct stm32_fmc2_nfc*) ; 
 int /*<<< orphan*/  stm32_fmc2_rw_page_init (struct nand_chip*,int,int /*<<< orphan*/ ,int) ; 
 int stm32_fmc2_select_chip (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int stm32_fmc2_xfer (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_fmc2_sequencer_read_page(struct nand_chip *chip, u8 *buf,
					  int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	u8 *ecc_calc = chip->ecc.calc_buf;
	u8 *ecc_code = chip->ecc.code_buf;
	u16 sta_map;
	int ret;

	/* Select the target */
	ret = stm32_fmc2_select_chip(chip, chip->cur_cs);
	if (ret)
		return ret;

	/* Configure the sequencer */
	stm32_fmc2_rw_page_init(chip, page, 0, false);

	/* Read the page */
	ret = stm32_fmc2_xfer(chip, buf, 0, false);
	if (ret)
		return ret;

	sta_map = stm32_fmc2_get_mapping_status(fmc2);

	/* Check if errors happen */
	if (likely(!sta_map)) {
		if (oob_required)
			return nand_change_read_column_op(chip, mtd->writesize,
							  chip->oob_poi,
							  mtd->oobsize, false);

		return 0;
	}

	/* Read oob */
	ret = nand_change_read_column_op(chip, mtd->writesize,
					 chip->oob_poi, mtd->oobsize, false);
	if (ret)
		return ret;

	ret = mtd_ooblayout_get_eccbytes(mtd, ecc_code, chip->oob_poi, 0,
					 chip->ecc.total);
	if (ret)
		return ret;

	/* Correct data */
	return chip->ecc.correct(chip, buf, ecc_code, ecc_calc);
}