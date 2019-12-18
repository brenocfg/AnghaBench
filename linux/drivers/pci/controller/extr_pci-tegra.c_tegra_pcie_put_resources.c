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
struct tegra_pcie_soc {scalar_t__ program_uphy; } ;
struct tegra_pcie {scalar_t__ irq; struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct tegra_pcie*) ; 
 int /*<<< orphan*/  tegra_pcie_phys_put (struct tegra_pcie*) ; 

__attribute__((used)) static int tegra_pcie_put_resources(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;

	if (pcie->irq > 0)
		free_irq(pcie->irq, pcie);

	if (soc->program_uphy)
		tegra_pcie_phys_put(pcie);

	return 0;
}