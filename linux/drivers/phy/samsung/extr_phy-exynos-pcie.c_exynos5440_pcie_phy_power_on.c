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
struct phy {int dummy; } ;
struct exynos_pcie_phy {int /*<<< orphan*/  phy_base; int /*<<< orphan*/  blk_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PHY_CMN_REG ; 
 int /*<<< orphan*/  PCIE_PHY_COMMON_PD_CMN ; 
 int /*<<< orphan*/  PCIE_PHY_COMMON_POWER ; 
 int /*<<< orphan*/  PCIE_PHY_COMMON_RESET ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV0_PD_TSV ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV0_POWER ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV1_PD_TSV ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV1_POWER ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV2_PD_TSV ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV2_POWER ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV3_PD_TSV ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV3_POWER ; 
 int /*<<< orphan*/  PCIE_PHY_TRSVREG_RESET ; 
 int /*<<< orphan*/  PCIE_PHY_TRSV_RESET ; 
 int /*<<< orphan*/  exynos_pcie_phy_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pcie_phy_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct exynos_pcie_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int exynos5440_pcie_phy_power_on(struct phy *phy)
{
	struct exynos_pcie_phy *ep = phy_get_drvdata(phy);
	u32 val;

	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_COMMON_RESET);
	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_CMN_REG);
	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_TRSVREG_RESET);
	exynos_pcie_phy_writel(ep->blk_base, 0, PCIE_PHY_TRSV_RESET);

	val = exynos_pcie_phy_readl(ep->phy_base, PCIE_PHY_COMMON_POWER);
	val &= ~PCIE_PHY_COMMON_PD_CMN;
	exynos_pcie_phy_writel(ep->phy_base, val, PCIE_PHY_COMMON_POWER);

	val = exynos_pcie_phy_readl(ep->phy_base, PCIE_PHY_TRSV0_POWER);
	val &= ~PCIE_PHY_TRSV0_PD_TSV;
	exynos_pcie_phy_writel(ep->phy_base, val, PCIE_PHY_TRSV0_POWER);

	val = exynos_pcie_phy_readl(ep->phy_base, PCIE_PHY_TRSV1_POWER);
	val &= ~PCIE_PHY_TRSV1_PD_TSV;
	exynos_pcie_phy_writel(ep->phy_base, val, PCIE_PHY_TRSV1_POWER);

	val = exynos_pcie_phy_readl(ep->phy_base, PCIE_PHY_TRSV2_POWER);
	val &= ~PCIE_PHY_TRSV2_PD_TSV;
	exynos_pcie_phy_writel(ep->phy_base, val, PCIE_PHY_TRSV2_POWER);

	val = exynos_pcie_phy_readl(ep->phy_base, PCIE_PHY_TRSV3_POWER);
	val &= ~PCIE_PHY_TRSV3_PD_TSV;
	exynos_pcie_phy_writel(ep->phy_base, val, PCIE_PHY_TRSV3_POWER);

	return 0;
}