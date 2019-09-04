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
struct TYPE_2__ {int /*<<< orphan*/  total; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_oob_region {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct mtd_info {int dummy; } ;
struct denali_nand_info {int /*<<< orphan*/  oob_skip_bytes; } ;

/* Variables and functions */
 int ERANGE ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int denali_ooblayout_ecc(struct mtd_info *mtd, int section,
				struct mtd_oob_region *oobregion)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	struct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		return -ERANGE;

	oobregion->offset = denali->oob_skip_bytes;
	oobregion->length = chip->ecc.total;

	return 0;
}