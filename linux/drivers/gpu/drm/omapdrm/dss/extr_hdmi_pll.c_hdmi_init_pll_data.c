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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dss_pll {char* name; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * hw; struct clk* clkin; int /*<<< orphan*/  base; int /*<<< orphan*/  id; } ;
struct hdmi_pll_data {TYPE_1__* wp; int /*<<< orphan*/  base; struct dss_pll pll; } ;
struct dss_device {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  DSS_PLL_HDMI ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dss_omap4_hdmi_pll_hw ; 
 int /*<<< orphan*/  dss_omap5_hdmi_pll_hw ; 
 int dss_pll_register (struct dss_device*,struct dss_pll*) ; 
 int /*<<< orphan*/  hdmi_pll_ops ; 

__attribute__((used)) static int hdmi_init_pll_data(struct dss_device *dss,
			      struct platform_device *pdev,
			      struct hdmi_pll_data *hpll)
{
	struct dss_pll *pll = &hpll->pll;
	struct clk *clk;
	int r;

	clk = devm_clk_get(&pdev->dev, "sys_clk");
	if (IS_ERR(clk)) {
		DSSERR("can't get sys_clk\n");
		return PTR_ERR(clk);
	}

	pll->name = "hdmi";
	pll->id = DSS_PLL_HDMI;
	pll->base = hpll->base;
	pll->clkin = clk;

	if (hpll->wp->version == 4)
		pll->hw = &dss_omap4_hdmi_pll_hw;
	else
		pll->hw = &dss_omap5_hdmi_pll_hw;

	pll->ops = &hdmi_pll_ops;

	r = dss_pll_register(dss, pll);
	if (r)
		return r;

	return 0;
}