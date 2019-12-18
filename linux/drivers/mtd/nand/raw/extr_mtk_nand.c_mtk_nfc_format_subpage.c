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
typedef  int u32 ;
struct TYPE_3__ {int size; int steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct TYPE_4__ {int sec; int /*<<< orphan*/  (* bm_swap ) (struct mtd_info*,int /*<<< orphan*/ ,int) ;} ;
struct mtk_nfc_fdm {int reg_size; } ;
struct mtk_nfc_nand_chip {TYPE_2__ bad_mark; struct mtk_nfc_fdm fdm; } ;
struct mtk_nfc {int /*<<< orphan*/  buffer; } ;
struct mtd_info {scalar_t__ oobsize; scalar_t__ writesize; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  data_ptr (struct nand_chip*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  mtk_data_ptr (struct nand_chip*,int) ; 
 int mtk_nfc_sector_encode (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_oob_ptr (struct nand_chip*,int) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  oob_ptr (struct nand_chip*,int) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_format_subpage(struct mtd_info *mtd, u32 offset,
				  u32 len, const u8 *buf)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	struct mtk_nfc_fdm *fdm = &mtk_nand->fdm;
	u32 start, end;
	int i, ret;

	start = offset / chip->ecc.size;
	end = DIV_ROUND_UP(offset + len, chip->ecc.size);

	memset(nfc->buffer, 0xff, mtd->writesize + mtd->oobsize);
	for (i = 0; i < chip->ecc.steps; i++) {
		memcpy(mtk_data_ptr(chip, i), data_ptr(chip, buf, i),
		       chip->ecc.size);

		if (start > i || i >= end)
			continue;

		if (i == mtk_nand->bad_mark.sec)
			mtk_nand->bad_mark.bm_swap(mtd, nfc->buffer, 1);

		memcpy(mtk_oob_ptr(chip, i), oob_ptr(chip, i), fdm->reg_size);

		/* program the CRC back to the OOB */
		ret = mtk_nfc_sector_encode(chip, mtk_data_ptr(chip, i));
		if (ret < 0)
			return ret;
	}

	return 0;
}