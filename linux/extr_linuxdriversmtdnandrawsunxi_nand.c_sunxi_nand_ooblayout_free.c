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
struct nand_ecc_ctrl {int steps; scalar_t__ mode; int bytes; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ NAND_ECC_HW ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int sunxi_nand_ooblayout_free(struct mtd_info *mtd, int section,
				     struct mtd_oob_region *oobregion)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &nand->ecc;

	if (section > ecc->steps)
		return -ERANGE;

	/*
	 * The first 2 bytes are used for BB markers, hence we
	 * only have 2 bytes available in the first user data
	 * section.
	 */
	if (!section && ecc->mode == NAND_ECC_HW) {
		oobregion->offset = 2;
		oobregion->length = 2;

		return 0;
	}

	oobregion->offset = section * (ecc->bytes + 4);

	if (section < ecc->steps)
		oobregion->length = 4;
	else
		oobregion->offset = mtd->oobsize - oobregion->offset;

	return 0;
}