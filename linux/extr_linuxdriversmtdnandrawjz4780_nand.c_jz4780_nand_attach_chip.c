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
struct TYPE_2__ {int bytes; int size; int strength; int mode; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  hwctl; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct jz4780_nand_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  bch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  NAND_ECC_HW 130 
#define  NAND_ECC_NONE 129 
#define  NAND_ECC_SOFT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int fls (int) ; 
 int /*<<< orphan*/  jz4780_nand_ecc_calculate ; 
 int /*<<< orphan*/  jz4780_nand_ecc_correct ; 
 int /*<<< orphan*/  jz4780_nand_ecc_hwctl ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_ooblayout_lp_ops ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct jz4780_nand_controller* to_jz4780_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4780_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct jz4780_nand_controller *nfc = to_jz4780_nand_controller(chip->controller);
	int eccbytes;

	chip->ecc.bytes = fls((1 + 8) * chip->ecc.size)	*
				(chip->ecc.strength / 8);

	switch (chip->ecc.mode) {
	case NAND_ECC_HW:
		if (!nfc->bch) {
			dev_err(nfc->dev,
				"HW BCH selected, but BCH controller not found\n");
			return -ENODEV;
		}

		chip->ecc.hwctl = jz4780_nand_ecc_hwctl;
		chip->ecc.calculate = jz4780_nand_ecc_calculate;
		chip->ecc.correct = jz4780_nand_ecc_correct;
		/* fall through */
	case NAND_ECC_SOFT:
		dev_info(nfc->dev, "using %s (strength %d, size %d, bytes %d)\n",
			 (nfc->bch) ? "hardware BCH" : "software ECC",
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

	mtd_set_ooblayout(mtd, &nand_ooblayout_lp_ops);

	return 0;
}