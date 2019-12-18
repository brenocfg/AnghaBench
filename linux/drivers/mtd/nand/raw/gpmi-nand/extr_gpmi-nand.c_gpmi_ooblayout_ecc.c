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
struct nand_chip {int dummy; } ;
struct mtd_oob_region {scalar_t__ length; scalar_t__ offset; } ;
struct mtd_info {scalar_t__ writesize; } ;
struct bch_geometry {scalar_t__ page_size; } ;
struct gpmi_nand_data {struct bch_geometry bch_geometry; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_ooblayout_ecc(struct mtd_info *mtd, int section,
			      struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	struct bch_geometry *geo = &this->bch_geometry;

	if (section)
		return -ERANGE;

	oobregion->offset = 0;
	oobregion->length = geo->page_size - mtd->writesize;

	return 0;
}