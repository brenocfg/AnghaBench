#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct TYPE_5__ {int reg_size; } ;
struct mtk_nfc_nand_chip {TYPE_2__ fdm; } ;
struct TYPE_6__ {int /*<<< orphan*/  op; int /*<<< orphan*/  mode; } ;
struct mtk_nfc {TYPE_3__ ecc_cfg; int /*<<< orphan*/  ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECC_DMA_MODE ; 
 int /*<<< orphan*/  ECC_ENCODE ; 
 int mtk_ecc_encode (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct mtk_nfc_nand_chip* to_mtk_nand (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_sector_encode(struct nand_chip *chip, u8 *data)
{
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	struct mtk_nfc_nand_chip *mtk_nand = to_mtk_nand(chip);
	int size = chip->ecc.size + mtk_nand->fdm.reg_size;

	nfc->ecc_cfg.mode = ECC_DMA_MODE;
	nfc->ecc_cfg.op = ECC_ENCODE;

	return mtk_ecc_encode(nfc->ecc, &nfc->ecc_cfg, data, size);
}