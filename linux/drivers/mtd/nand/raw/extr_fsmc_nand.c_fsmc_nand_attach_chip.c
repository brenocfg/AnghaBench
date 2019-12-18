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
struct TYPE_2__ {int mode; int bytes; int strength; int /*<<< orphan*/  algo; int /*<<< orphan*/  options; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int oobsize; } ;
struct fsmc_nand_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int AMBA_REV_BITS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  NAND_ECC_BCH ; 
#define  NAND_ECC_HW 130 
#define  NAND_ECC_ON_DIE 129 
#define  NAND_ECC_SOFT 128 
 int /*<<< orphan*/  NAND_ECC_SOFT_HAMMING_SM_ORDER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fsmc_ecc1_ooblayout_ops ; 
 int /*<<< orphan*/  fsmc_ecc4_ooblayout_ops ; 
 int /*<<< orphan*/  fsmc_read_hwecc_ecc1 ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_correct_data ; 
 struct fsmc_nand_data* nand_to_fsmc (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int fsmc_nand_attach_chip(struct nand_chip *nand)
{
	struct mtd_info *mtd = nand_to_mtd(nand);
	struct fsmc_nand_data *host = nand_to_fsmc(nand);

	if (AMBA_REV_BITS(host->pid) >= 8) {
		switch (mtd->oobsize) {
		case 16:
		case 64:
		case 128:
		case 224:
		case 256:
			break;
		default:
			dev_warn(host->dev,
				 "No oob scheme defined for oobsize %d\n",
				 mtd->oobsize);
			return -EINVAL;
		}

		mtd_set_ooblayout(mtd, &fsmc_ecc4_ooblayout_ops);

		return 0;
	}

	switch (nand->ecc.mode) {
	case NAND_ECC_HW:
		dev_info(host->dev, "Using 1-bit HW ECC scheme\n");
		nand->ecc.calculate = fsmc_read_hwecc_ecc1;
		nand->ecc.correct = nand_correct_data;
		nand->ecc.bytes = 3;
		nand->ecc.strength = 1;
		nand->ecc.options |= NAND_ECC_SOFT_HAMMING_SM_ORDER;
		break;

	case NAND_ECC_SOFT:
		if (nand->ecc.algo == NAND_ECC_BCH) {
			dev_info(host->dev,
				 "Using 4-bit SW BCH ECC scheme\n");
			break;
		}

	case NAND_ECC_ON_DIE:
		break;

	default:
		dev_err(host->dev, "Unsupported ECC mode!\n");
		return -ENOTSUPP;
	}

	/*
	 * Don't set layout for BCH4 SW ECC. This will be
	 * generated later in nand_bch_init() later.
	 */
	if (nand->ecc.mode == NAND_ECC_HW) {
		switch (mtd->oobsize) {
		case 16:
		case 64:
		case 128:
			mtd_set_ooblayout(mtd,
					  &fsmc_ecc1_ooblayout_ops);
			break;
		default:
			dev_warn(host->dev,
				 "No oob scheme defined for oobsize %d\n",
				 mtd->oobsize);
			return -EINVAL;
		}
	}

	return 0;
}