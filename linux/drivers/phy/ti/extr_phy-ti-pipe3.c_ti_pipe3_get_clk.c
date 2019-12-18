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
struct ti_pipe3 {scalar_t__ mode; struct clk* div_clk; struct clk* sys_clk; scalar_t__ phy_power_syscon; struct clk* wkupclk; struct clk* refclk; struct device* dev; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ PIPE3_MODE_PCIE ; 
 scalar_t__ PIPE3_MODE_SATA ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int ti_pipe3_get_clk(struct ti_pipe3 *phy)
{
	struct clk *clk;
	struct device *dev = phy->dev;

	phy->refclk = devm_clk_get(dev, "refclk");
	if (IS_ERR(phy->refclk)) {
		dev_err(dev, "unable to get refclk\n");
		/* older DTBs have missing refclk in SATA PHY
		 * so don't bail out in case of SATA PHY.
		 */
		if (phy->mode != PIPE3_MODE_SATA)
			return PTR_ERR(phy->refclk);
	}

	if (phy->mode != PIPE3_MODE_SATA) {
		phy->wkupclk = devm_clk_get(dev, "wkupclk");
		if (IS_ERR(phy->wkupclk)) {
			dev_err(dev, "unable to get wkupclk\n");
			return PTR_ERR(phy->wkupclk);
		}
	} else {
		phy->wkupclk = ERR_PTR(-ENODEV);
	}

	if (phy->mode != PIPE3_MODE_PCIE || phy->phy_power_syscon) {
		phy->sys_clk = devm_clk_get(dev, "sysclk");
		if (IS_ERR(phy->sys_clk)) {
			dev_err(dev, "unable to get sysclk\n");
			return -EINVAL;
		}
	}

	if (phy->mode == PIPE3_MODE_PCIE) {
		clk = devm_clk_get(dev, "dpll_ref");
		if (IS_ERR(clk)) {
			dev_err(dev, "unable to get dpll ref clk\n");
			return PTR_ERR(clk);
		}
		clk_set_rate(clk, 1500000000);

		clk = devm_clk_get(dev, "dpll_ref_m2");
		if (IS_ERR(clk)) {
			dev_err(dev, "unable to get dpll ref m2 clk\n");
			return PTR_ERR(clk);
		}
		clk_set_rate(clk, 100000000);

		clk = devm_clk_get(dev, "phy-div");
		if (IS_ERR(clk)) {
			dev_err(dev, "unable to get phy-div clk\n");
			return PTR_ERR(clk);
		}
		clk_set_rate(clk, 100000000);

		phy->div_clk = devm_clk_get(dev, "div-clk");
		if (IS_ERR(phy->div_clk)) {
			dev_err(dev, "unable to get div-clk\n");
			return PTR_ERR(phy->div_clk);
		}
	} else {
		phy->div_clk = ERR_PTR(-ENODEV);
	}

	return 0;
}