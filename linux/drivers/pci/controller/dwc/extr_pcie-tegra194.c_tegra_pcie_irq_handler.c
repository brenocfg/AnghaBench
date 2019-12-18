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
struct tegra_pcie_dw {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_pcie_rp_irq_handler (struct tegra_pcie_dw*) ; 

__attribute__((used)) static irqreturn_t tegra_pcie_irq_handler(int irq, void *arg)
{
	struct tegra_pcie_dw *pcie = arg;

	return tegra_pcie_rp_irq_handler(pcie);
}