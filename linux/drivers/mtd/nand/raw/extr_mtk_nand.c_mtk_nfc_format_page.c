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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ steps; int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct TYPE_4__ {scalar_t__ sec; int /*<<< orphan*/  (* bm_swap ) (struct mtd_info*,int /*<<< orphan*/ ,int) ;} ;
struct mtk_nfc_fdm {int /*<<< orphan*/  reg_size; } ;
struct mtk_nfc_nand_chip {TYPE_2__ bad_mark; struct mtk_nfc_fdm fdm; } ;
struct mtk_nfc {int /*<<< orphan*/  buffer; } ;
struct mtd_info {scalar_t__ oobsize; scalar_t__ writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_ptr (struct nand_chip*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  mtk_data_ptr (struct nand_chip*,scalar_t__) ; 
 int /*<<< orphan*/  mtk_oob_ptr (struct nand_chip*,scalar_t__) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  oob_ptr (struct nand_chip*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static void mtk_nfc_format_page(struct mtd_info *mtd, const u8 *buf)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	struct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 i;

	memset(nfc->buffer, 0xff, mtd->writesize + mtd->oobsize);
	for (i = 0; i < chip->ecc.steps; i++) {
		if (buf)
			memcpy(mtk_data_ptr(chip, i), data_ptr(chip, buf, i),
			       chip->ecc.size);

		if (i == mtk_nand->bad_mark.sec)
			mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, 1);

		memcpy(mtk_oob_ptr(chip, i), oob_ptr(chip, i), fdm->reg_size);
	}
}