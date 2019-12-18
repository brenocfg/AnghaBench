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
struct phy {int dummy; } ;
struct exynos_pcie_phy {int /*<<< orphan*/  blk_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PHY_GLOBAL_RESET ; 
 int /*<<< orphan*/  PCIE_PHY_MAC_RESET ; 
 int /*<<< orphan*/  exynos_pcie_phy_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct exynos_pcie_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int exynos5440_pcie_phy_reset(struct phy *phy)
{
	struct exynos_pcie_phy *ep = phy_get_drvdata(phy);

	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_MAC_RESET);
	exynos_pcie_phy_writel(ep->blk_base, 1, PCIE_PHY_GLOBAL_RESET);
	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_GLOBAL_RESET);

	return 0;
}