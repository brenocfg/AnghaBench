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
struct tegra_pcie_dw {int /*<<< orphan*/ * slot_ctl_12v; int /*<<< orphan*/  dev; int /*<<< orphan*/ * slot_ctl_3v3; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* devm_regulator_get_optional (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tegra_pcie_get_slot_regulators(struct tegra_pcie_dw *pcie)
{
	pcie->slot_ctl_3v3 = devm_regulator_get_optional(pcie->dev, "vpcie3v3");
	if (IS_ERR(pcie->slot_ctl_3v3)) {
		if (PTR_ERR(pcie->slot_ctl_3v3) != -ENODEV)
			return PTR_ERR(pcie->slot_ctl_3v3);

		pcie->slot_ctl_3v3 = NULL;
	}

	pcie->slot_ctl_12v = devm_regulator_get_optional(pcie->dev, "vpcie12v");
	if (IS_ERR(pcie->slot_ctl_12v)) {
		if (PTR_ERR(pcie->slot_ctl_12v) != -ENODEV)
			return PTR_ERR(pcie->slot_ctl_12v);

		pcie->slot_ctl_12v = NULL;
	}

	return 0;
}