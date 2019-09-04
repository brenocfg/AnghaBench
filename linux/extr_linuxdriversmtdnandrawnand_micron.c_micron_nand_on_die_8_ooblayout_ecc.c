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
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_oob_region {scalar_t__ length; scalar_t__ offset; } ;
struct mtd_info {scalar_t__ oobsize; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int micron_nand_on_die_8_ooblayout_ecc(struct mtd_info *mtd,
					      int section,
					      struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		return -ERANGE;

	oobregion->offset = mtd->oobsize - chip->ecc.total;
	oobregion->length = chip->ecc.total;

	return 0;
}