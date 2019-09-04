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
typedef  int u32 ;
struct TYPE_3__ {int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct TYPE_4__ {int reg_size; } ;
struct mtk_nfc_nand_chip {TYPE_2__ fdm; } ;
struct mtd_oob_region {int offset; scalar_t__ length; } ;
struct mtd_info {int writesize; scalar_t__ oobsize; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_ooblayout_ecc(struct mtd_info *mtd, int section,
				 struct mtd_oob_region *oob_region)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	u32 eccsteps;

	if (section)
		return -ERANGE;

	eccsteps = mtd->writesize / chip->ecc.size;
	oob_region->offset = mtk_nand->fdm.reg_size * eccsteps;
	oob_region->length = mtd->oobsize - oob_region->offset;

	return 0;
}