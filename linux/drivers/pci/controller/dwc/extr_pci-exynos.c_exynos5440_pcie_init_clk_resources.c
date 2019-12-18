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
struct exynos_pcie {TYPE_1__* clk_res; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  bus_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int exynos5440_pcie_init_clk_resources(struct exynos_pcie *ep)
{
	struct dw_pcie *pci = ep->pci;
	struct device *dev = pci->dev;
	int ret;

	ret = clk_prepare_enable(ep->clk_res->clk);
	if (ret) {
		dev_err(dev, "cannot enable pcie rc clock");
		return ret;
	}

	ret = clk_prepare_enable(ep->clk_res->bus_clk);
	if (ret) {
		dev_err(dev, "cannot enable pcie bus clock");
		goto err_bus_clk;
	}

	return 0;

err_bus_clk:
	clk_disable_unprepare(ep->clk_res->clk);

	return ret;
}