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
struct TYPE_2__ {scalar_t__ total; } ;
struct nand_chip {int options; TYPE_1__ ecc; } ;
struct omap_nand_info {scalar_t__ ecc_opt; struct nand_chip nand; } ;
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int BADBLOCK_MARKER_LENGTH ; 
 int ERANGE ; 
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ OMAP_ECC_HAM1_CODE_HW ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 

__attribute__((used)) static int omap_ooblayout_free(struct mtd_info *mtd, int section,
			       struct mtd_oob_region *oobregion)
{
	struct omap_nand_info *info = mtd_to_omap(mtd);
	struct nand_chip *chip = &info->nand;
	int off = BADBLOCK_MARKER_LENGTH;

	if (info->ecc_opt == OMAP_ECC_HAM1_CODE_HW &&
	    !(chip->options & NAND_BUSWIDTH_16))
		off = 1;

	if (section)
		return -ERANGE;

	off += chip->ecc.total;
	if (off >= mtd->oobsize)
		return -ERANGE;

	oobregion->offset = off;
	oobregion->length = mtd->oobsize - off;

	return 0;
}