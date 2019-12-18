#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nand_ecc_ctrl {int /*<<< orphan*/  total; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct mtd_oob_region {int offset; int /*<<< orphan*/  length; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int nand_ooblayout_ecc_lp_hamming(struct mtd_info *mtd, int section,
					 struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;

	if (section)
		return -ERANGE;

	switch (mtd->oobsize) {
	case 64:
		oobregion->offset = 40;
		break;
	case 128:
		oobregion->offset = 80;
		break;
	default:
		return -EINVAL;
	}

	oobregion->length = ecc->total;
	if (oobregion->offset + oobregion->length > mtd->oobsize)
		return -ERANGE;

	return 0;
}