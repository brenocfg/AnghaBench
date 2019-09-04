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
struct tegra_nand_controller {int cur_cs; } ;
struct tegra_nand_chip {int* cs; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct tegra_nand_chip* to_tegra_chip (struct nand_chip*) ; 
 struct tegra_nand_controller* to_tegra_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_nand_select_chip(struct mtd_info *mtd, int die_nr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct tegra_nand_chip *nand = to_tegra_chip(chip);
	struct tegra_nand_controller *ctrl = to_tegra_ctrl(chip->controller);

	WARN_ON(die_nr >= (int)ARRAY_SIZE(nand->cs));

	if (die_nr < 0 || die_nr > 0) {
		ctrl->cur_cs = -1;
		return;
	}

	ctrl->cur_cs = nand->cs[die_nr];
}