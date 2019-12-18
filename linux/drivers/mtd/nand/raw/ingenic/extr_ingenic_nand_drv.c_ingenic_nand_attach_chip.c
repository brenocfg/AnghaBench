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
struct TYPE_3__ {int strength; int bytes; int size; int mode; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  hwctl; } ;
struct nand_chip {int bbt_options; TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct ingenic_nfc {TYPE_2__* soc_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  ecc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * oob_layout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
#define  NAND_ECC_HW 130 
#define  NAND_ECC_NONE 129 
#define  NAND_ECC_SOFT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int fls (int) ; 
 int /*<<< orphan*/  ingenic_nand_ecc_calculate ; 
 int /*<<< orphan*/  ingenic_nand_ecc_correct ; 
 int /*<<< orphan*/  ingenic_nand_ecc_hwctl ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  qi_lb60_ooblayout_ops ; 
 struct ingenic_nfc* to_ingenic_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ingenic_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct ingenic_nfc *nfc = to_ingenic_nfc(chip->controller);
	int eccbytes;

	if (chip->ecc.strength == 4) {
		/* JZ4740 uses 9 bytes of ECC to correct maximum 4 errors */
		chip->ecc.bytes = 9;
	} else {
		chip->ecc.bytes = fls((1 + 8) * chip->ecc.size)	*
				  (chip->ecc.strength / 8);
	}

	switch (chip->ecc.mode) {
	case NAND_ECC_HW:
		if (!nfc->ecc) {
			dev_err(nfc->dev, "HW ECC selected, but ECC controller not found\n");
			return -ENODEV;
		}

		chip->ecc.hwctl = ingenic_nand_ecc_hwctl;
		chip->ecc.calculate = ingenic_nand_ecc_calculate;
		chip->ecc.correct = ingenic_nand_ecc_correct;
		/* fall through */
	case NAND_ECC_SOFT:
		dev_info(nfc->dev, "using %s (strength %d, size %d, bytes %d)\n",
			 (nfc->ecc) ? "hardware ECC" : "software ECC",
			 chip->ecc.strength, chip->ecc.size, chip->ecc.bytes);
		break;
	case NAND_ECC_NONE:
		dev_info(nfc->dev, "not using ECC\n");
		break;
	default:
		dev_err(nfc->dev, "ECC mode %d not supported\n",
			chip->ecc.mode);
		return -EINVAL;
	}

	/* The NAND core will generate the ECC layout for SW ECC */
	if (chip->ecc.mode != NAND_ECC_HW)
		return 0;

	/* Generate ECC layout. ECC codes are right aligned in the OOB area. */
	eccbytes = mtd->writesize / chip->ecc.size * chip->ecc.bytes;

	if (eccbytes > mtd->oobsize - 2) {
		dev_err(nfc->dev,
			"invalid ECC config: required %d ECC bytes, but only %d are available",
			eccbytes, mtd->oobsize - 2);
		return -EINVAL;
	}

	/*
	 * The generic layout for BBT markers will most likely overlap with our
	 * ECC bytes in the OOB, so move the BBT markers outside the OOB area.
	 */
	if (chip->bbt_options & NAND_BBT_USE_FLASH)
		chip->bbt_options |= NAND_BBT_NO_OOB;

	/* For legacy reasons we use a different layout on the qi,lb60 board. */
	if (of_machine_is_compatible("qi,lb60"))
		mtd_set_ooblayout(mtd, &qi_lb60_ooblayout_ops);
	else
		mtd_set_ooblayout(mtd, nfc->soc_info->oob_layout);

	return 0;
}