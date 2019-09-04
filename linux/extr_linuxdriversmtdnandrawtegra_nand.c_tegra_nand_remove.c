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
struct tegra_nand_controller {int /*<<< orphan*/  clk; struct nand_chip* chip; } ;
struct platform_device {int dummy; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int mtd_device_unregister (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct tegra_nand_controller* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tegra_nand_remove(struct platform_device *pdev)
{
	struct tegra_nand_controller *ctrl = platform_get_drvdata(pdev);
	struct nand_chip *chip = ctrl->chip;
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	ret = mtd_device_unregister(mtd);
	if (ret)
		return ret;

	nand_cleanup(chip);

	clk_disable_unprepare(ctrl->clk);

	return 0;
}