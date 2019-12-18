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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_INTR_MASK ; 
 int /*<<< orphan*/  AFI_INTR_MASK_INT_MASK ; 
 int /*<<< orphan*/  afi_readl (struct tegra_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afi_writel (struct tegra_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_pcie_disable_interrupts(struct tegra_pcie *pcie)
{
	u32 value;

	value = afi_readl(pcie, AFI_INTR_MASK);
	value &= ~AFI_INTR_MASK_INT_MASK;
	afi_writel(pcie, value, AFI_INTR_MASK);
}