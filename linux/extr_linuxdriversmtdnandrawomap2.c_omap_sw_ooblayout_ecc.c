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
struct TYPE_2__ {int steps; int bytes; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int BADBLOCK_MARKER_LENGTH ; 
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int omap_sw_ooblayout_ecc(struct mtd_info *mtd, int section,
				 struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int off = BADBLOCK_MARKER_LENGTH;

	if (section >= chip->ecc.steps)
		return -ERANGE;

	/*
	 * When SW correction is employed, one OMAP specific marker byte is
	 * reserved after each ECC step.
	 */
	oobregion->offset = off + (section * (chip->ecc.bytes + 1));
	oobregion->length = chip->ecc.bytes;

	return 0;
}