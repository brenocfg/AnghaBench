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
struct tegra_nand_controller {scalar_t__ regs; } ;
struct tegra_nand_chip {int /*<<< orphan*/  config; int /*<<< orphan*/  config_ecc; int /*<<< orphan*/  bch_config; } ;
struct TYPE_2__ {scalar_t__ algo; } ;
struct nand_chip {TYPE_1__ ecc; } ;

/* Variables and functions */
 scalar_t__ BCH_CONFIG ; 
 scalar_t__ CONFIG ; 
 scalar_t__ NAND_ECC_BCH ; 
 struct tegra_nand_chip* to_tegra_chip (struct nand_chip*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra_nand_hw_ecc(struct tegra_nand_controller *ctrl,
			      struct nand_chip *chip, bool enable)
{
	struct tegra_nand_chip *nand = to_tegra_chip(chip);

	if (chip->ecc.algo == NAND_ECC_BCH && enable)
		writel_relaxed(nand->bch_config, ctrl->regs + BCH_CONFIG);
	else
		writel_relaxed(0, ctrl->regs + BCH_CONFIG);

	if (enable)
		writel_relaxed(nand->config_ecc, ctrl->regs + CONFIG);
	else
		writel_relaxed(nand->config, ctrl->regs + CONFIG);
}