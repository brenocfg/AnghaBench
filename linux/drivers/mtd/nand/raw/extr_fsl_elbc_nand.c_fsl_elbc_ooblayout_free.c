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
struct TYPE_2__ {int steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct fsl_elbc_mtd {int fmr; } ;

/* Variables and functions */
 int ERANGE ; 
 int FMR_ECCM ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct fsl_elbc_mtd* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int fsl_elbc_ooblayout_free(struct mtd_info *mtd, int section,
				   struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);

	if (section > chip->ecc.steps)
		return -ERANGE;

	if (!section) {
		oobregion->offset = 0;
		if (mtd->writesize > 512)
			oobregion->offset++;
		oobregion->length = (priv->fmr & FMR_ECCM) ? 7 : 5;
	} else {
		oobregion->offset = (16 * section) -
				    ((priv->fmr & FMR_ECCM) ? 5 : 7);
		if (section < chip->ecc.steps)
			oobregion->length = 13;
		else
			oobregion->length = mtd->oobsize - oobregion->offset;
	}

	return 0;
}