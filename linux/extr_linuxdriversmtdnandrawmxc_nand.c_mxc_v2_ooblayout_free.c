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
struct TYPE_2__ {int bytes; int steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int mxc_v2_ooblayout_free(struct mtd_info *mtd, int section,
				 struct mtd_oob_region *oobregion)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	int stepsize = nand_chip->ecc.bytes == 9 ? 16 : 26;

	if (section >= nand_chip->ecc.steps)
		return -ERANGE;

	if (!section) {
		if (mtd->writesize <= 512) {
			oobregion->offset = 0;
			oobregion->length = 5;
		} else {
			oobregion->offset = 2;
			oobregion->length = 4;
		}
	} else {
		oobregion->offset = section * stepsize;
		oobregion->length = 7;
	}

	return 0;
}