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
struct nand_chip {int dummy; } ;
struct mtd_oob_region {scalar_t__ length; scalar_t__ offset; } ;
struct mtd_info {scalar_t__ oobsize; } ;
struct marvell_hw_ecc_layout {int full_chunk_cnt; int ecc_bytes; scalar_t__ last_ecc_bytes; } ;
struct TYPE_2__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int ERANGE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 TYPE_1__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nand_ooblayout_ecc(struct mtd_info *mtd, int section,
				      struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;

	if (section)
		return -ERANGE;

	oobregion->length = (lt->full_chunk_cnt * lt->ecc_bytes) +
			    lt->last_ecc_bytes;
	oobregion->offset = mtd->oobsize - oobregion->length;

	return 0;
}