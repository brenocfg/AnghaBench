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
struct TYPE_2__ {int strength; int steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_oob_region {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int BITS_PER_STEP_RS ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int ERANGE ; 
 int /*<<< orphan*/  SKIP_SPARE_BYTES ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  round_up (int,int) ; 

__attribute__((used)) static int tegra_nand_ooblayout_rs_ecc(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *oobregion)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int bytes_per_step = DIV_ROUND_UP(BITS_PER_STEP_RS * chip->ecc.strength,
					  BITS_PER_BYTE);

	if (section > 0)
		return -ERANGE;

	oobregion->offset = SKIP_SPARE_BYTES;
	oobregion->length = round_up(bytes_per_step * chip->ecc.steps, 4);

	return 0;
}