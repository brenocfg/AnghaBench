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
struct exynos_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pcie_enable_irq_pulse (struct exynos_pcie*) ; 
 int /*<<< orphan*/  exynos_pcie_msi_init (struct exynos_pcie*) ; 

__attribute__((used)) static void exynos_pcie_enable_interrupts(struct exynos_pcie *ep)
{
	exynos_pcie_enable_irq_pulse(ep);

	if (IS_ENABLED(CONFIG_PCI_MSI))
		exynos_pcie_msi_init(ep);
}