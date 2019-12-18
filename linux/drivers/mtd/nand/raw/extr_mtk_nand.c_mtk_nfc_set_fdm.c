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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int strength; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtk_nfc_nand_chip {scalar_t__ spare_per_sector; } ;
struct mtk_nfc_fdm {scalar_t__ reg_size; int ecc_size; } ;
struct mtk_nfc {int /*<<< orphan*/  ecc; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 scalar_t__ NFI_FDM_MAX_SIZE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int mtk_ecc_get_parity_bits (int /*<<< orphan*/ ) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static void mtk_nfc_set_fdm(struct mtk_nfc_fdm *fdm, struct mtd_info *mtd)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mtk_nfc_nand_chip *chip = to_mtk_nand(nand);
	struct mtk_nfc *nfc = nand_get_controller_data(nand);
	u32 ecc_bytes;

	ecc_bytes = DIV_ROUND_UP(nand->ecc.strength *
				 mtk_ecc_get_parity_bits(nfc->ecc), 8);

	fdm->reg_size = chip->spare_per_sector - ecc_bytes;
	if (fdm->reg_size > NFI_FDM_MAX_SIZE)
		fdm->reg_size = NFI_FDM_MAX_SIZE;

	/* bad block mark storage */
	fdm->ecc_size = 1;
}