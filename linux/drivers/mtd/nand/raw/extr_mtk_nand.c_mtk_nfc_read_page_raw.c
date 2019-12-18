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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int steps; int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_2__ ecc; } ;
struct TYPE_3__ {int sec; int /*<<< orphan*/  (* bm_swap ) (struct mtd_info*,int /*<<< orphan*/ ,int) ;} ;
struct mtk_nfc_fdm {int /*<<< orphan*/  reg_size; } ;
struct mtk_nfc_nand_chip {TYPE_1__ bad_mark; struct mtk_nfc_fdm fdm; } ;
struct mtk_nfc {int /*<<< orphan*/  buffer; } ;
struct mtd_info {scalar_t__ writesize; scalar_t__ oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_ptr (struct nand_chip*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  mtk_data_ptr (struct nand_chip*,int) ; 
 int mtk_nfc_read_subpage (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mtk_oob_ptr (struct nand_chip*,int) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  oob_ptr (struct nand_chip*,int) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_read_page_raw(struct nand_chip *chip, u8 *buf, int oob_on,
				 int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	struct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	int i, ret;

	memset(nfc->buffer, 0xff, mtd->writesize + mtd->oobsize);
	ret = mtk_nfc_read_subpage(mtd, chip, 0, mtd->writesize, nfc->buffer,
				   page, 1);
	if (ret < 0)
		return ret;

	for (i = 0; i < chip->ecc.steps; i++) {
		memcpy(oob_ptr(chip, i), mtk_oob_ptr(chip, i), fdm->reg_size);

		if (i == mtk_nand->bad_mark.sec)
			mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, 1);

		if (buf)
			memcpy(data_ptr(chip, buf, i), mtk_data_ptr(chip, i),
			       chip->ecc.size);
	}

	return ret;
}