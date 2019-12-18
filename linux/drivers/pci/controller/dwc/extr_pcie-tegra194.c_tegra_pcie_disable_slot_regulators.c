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
struct tegra_pcie_dw {scalar_t__ slot_ctl_3v3; scalar_t__ slot_ctl_12v; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static void tegra_pcie_disable_slot_regulators(struct tegra_pcie_dw *pcie)
{
	if (pcie->slot_ctl_12v)
		regulator_disable(pcie->slot_ctl_12v);
	if (pcie->slot_ctl_3v3)
		regulator_disable(pcie->slot_ctl_3v3);
}