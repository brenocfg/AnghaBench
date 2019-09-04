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
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {scalar_t__ writesize; } ;
struct marvell_hw_ecc_layout {scalar_t__ data_bytes; int full_chunk_cnt; int spare_bytes; int last_spare_bytes; } ;
struct TYPE_2__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ SZ_2K ; 
 scalar_t__ SZ_4K ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 TYPE_1__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nand_ooblayout_free(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;

	if (section)
		return -ERANGE;

	/*
	 * Bootrom looks in bytes 0 & 5 for bad blocks for the
	 * 4KB page / 4bit BCH combination.
	 */
	if (mtd->writesize == SZ_4K && lt->data_bytes == SZ_2K)
		oobregion->offset = 6;
	else
		oobregion->offset = 2;

	oobregion->length = (lt->full_chunk_cnt * lt->spare_bytes) +
			    lt->last_spare_bytes - oobregion->offset;

	return 0;
}