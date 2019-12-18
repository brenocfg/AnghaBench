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
struct nand_ecc_ctrl {int mode; int size; int strength; } ;
struct TYPE_4__ {int step_size; int strength; } ;
struct TYPE_5__ {TYPE_1__ eccreq; } ;
struct nand_chip {TYPE_2__ base; int /*<<< orphan*/  controller; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct marvell_nfc {int /*<<< orphan*/  dev; TYPE_3__* caps; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_nfcv2; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NAND_ECC_HW 131 
#define  NAND_ECC_NONE 130 
#define  NAND_ECC_ON_DIE 129 
#define  NAND_ECC_SOFT 128 
 int /*<<< orphan*/  SZ_2K ; 
 int /*<<< orphan*/  SZ_512 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int marvell_nand_hw_ecc_ctrl_init (struct mtd_info*,struct nand_ecc_ctrl*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nand_ecc_init(struct mtd_info *mtd,
				 struct nand_ecc_ctrl *ecc)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	int ret;

	if (ecc->mode != NAND_ECC_NONE && (!ecc->size || !ecc->strength)) {
		if (chip->base.eccreq.step_size && chip->base.eccreq.strength) {
			ecc->size = chip->base.eccreq.step_size;
			ecc->strength = chip->base.eccreq.strength;
		} else {
			dev_info(nfc->dev,
				 "No minimum ECC strength, using 1b/512B\n");
			ecc->size = 512;
			ecc->strength = 1;
		}
	}

	switch (ecc->mode) {
	case NAND_ECC_HW:
		ret = marvell_nand_hw_ecc_ctrl_init(mtd, ecc);
		if (ret)
			return ret;
		break;
	case NAND_ECC_NONE:
	case NAND_ECC_SOFT:
	case NAND_ECC_ON_DIE:
		if (!nfc->caps->is_nfcv2 && mtd->writesize != SZ_512 &&
		    mtd->writesize != SZ_2K) {
			dev_err(nfc->dev, "NFCv1 cannot write %d bytes pages\n",
				mtd->writesize);
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}