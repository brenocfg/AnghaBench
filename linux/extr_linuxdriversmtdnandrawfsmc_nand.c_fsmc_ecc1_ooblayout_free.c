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
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int fsmc_ecc1_ooblayout_free(struct mtd_info *mtd, int section,
				    struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		return -ERANGE;

	oobregion->offset = (section * 16) + 8;

	if (section < chip->ecc.steps - 1)
		oobregion->length = 8;
	else
		oobregion->length = mtd->oobsize - oobregion->offset;

	return 0;
}