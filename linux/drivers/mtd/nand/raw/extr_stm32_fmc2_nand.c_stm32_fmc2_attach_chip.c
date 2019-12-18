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
struct stm32_fmc2_nfc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ mode; int size; } ;
struct nand_chip {int bbt_options; int options; TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; scalar_t__ oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FMC2_BBM_LEN ; 
 int FMC2_MAX_SG ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ NAND_ECC_HW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int nand_ecc_choose_conf (struct nand_chip*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stm32_fmc2_ecc_caps ; 
 int /*<<< orphan*/  stm32_fmc2_nand_callbacks_setup (struct nand_chip*) ; 
 int /*<<< orphan*/  stm32_fmc2_nand_ooblayout_ops ; 
 int /*<<< orphan*/  stm32_fmc2_set_buswidth_16 (struct stm32_fmc2_nfc*,int) ; 
 struct stm32_fmc2_nfc* to_stm32_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_fmc2_attach_chip(struct nand_chip *chip)
{
	struct stm32_fmc2_nfc *fmc2 = to_stm32_nfc(chip->controller);
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	/*
	 * Only NAND_ECC_HW mode is actually supported
	 * Hamming => ecc.strength = 1
	 * BCH4 => ecc.strength = 4
	 * BCH8 => ecc.strength = 8
	 * ECC sector size = 512
	 */
	if (chip->ecc.mode != NAND_ECC_HW) {
		dev_err(fmc2->dev, "nand_ecc_mode is not well defined in the DT\n");
		return -EINVAL;
	}

	ret = nand_ecc_choose_conf(chip, &stm32_fmc2_ecc_caps,
				   mtd->oobsize - FMC2_BBM_LEN);
	if (ret) {
		dev_err(fmc2->dev, "no valid ECC settings set\n");
		return ret;
	}

	if (mtd->writesize / chip->ecc.size > FMC2_MAX_SG) {
		dev_err(fmc2->dev, "nand page size is not supported\n");
		return -EINVAL;
	}

	if (chip->bbt_options & NAND_BBT_USE_FLASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;

	/* NAND callbacks setup */
	stm32_fmc2_nand_callbacks_setup(chip);

	/* Define ECC layout */
	mtd_set_ooblayout(mtd, &stm32_fmc2_nand_ooblayout_ops);

	/* Configure bus width to 16-bit */
	if (chip->options & NAND_BUSWIDTH_16)
		stm32_fmc2_set_buswidth_16(fmc2, true);

	return 0;
}