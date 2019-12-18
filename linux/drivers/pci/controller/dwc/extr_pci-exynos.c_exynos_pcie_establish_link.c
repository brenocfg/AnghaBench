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
struct pcie_port {int dummy; } ;
struct exynos_pcie {int /*<<< orphan*/  phy; TYPE_1__* mem_res; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; struct pcie_port pp; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  elbi_base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PCIE_APP_LTSSM_ENABLE ; 
 int PCIE_ELBI_LTSSM_ENABLE ; 
 int /*<<< orphan*/  PCIE_PWR_RESET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int /*<<< orphan*/  dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  exynos_pcie_assert_core_reset (struct exynos_pcie*) ; 
 int /*<<< orphan*/  exynos_pcie_assert_reset (struct exynos_pcie*) ; 
 int /*<<< orphan*/  exynos_pcie_deassert_core_reset (struct exynos_pcie*) ; 
 int /*<<< orphan*/  exynos_pcie_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_pcie_establish_link(struct exynos_pcie *ep)
{
	struct dw_pcie *pci = ep->pci;
	struct pcie_port *pp = &pci->pp;
	struct device *dev = pci->dev;

	if (dw_pcie_link_up(pci)) {
		dev_err(dev, "Link already up\n");
		return 0;
	}

	exynos_pcie_assert_core_reset(ep);

	phy_reset(ep->phy);

	exynos_pcie_writel(ep->mem_res->elbi_base, 1,
			PCIE_PWR_RESET);

	phy_power_on(ep->phy);
	phy_init(ep->phy);

	exynos_pcie_deassert_core_reset(ep);
	dw_pcie_setup_rc(pp);
	exynos_pcie_assert_reset(ep);

	/* assert LTSSM enable */
	exynos_pcie_writel(ep->mem_res->elbi_base, PCIE_ELBI_LTSSM_ENABLE,
			  PCIE_APP_LTSSM_ENABLE);

	/* check if the link is up or not */
	if (!dw_pcie_wait_for_link(pci))
		return 0;

	phy_power_off(ep->phy);
	return -ETIMEDOUT;
}