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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dss_pll {char* name; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * hw; struct clk* clkin; int /*<<< orphan*/  base; int /*<<< orphan*/  id; } ;
struct hdmi_pll_data {int /*<<< orphan*/  base; struct dss_pll pll; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  DSS_PLL_HDMI ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct clk*) ; 
#define  OMAPDSS_VER_DRA7xx 132 
#define  OMAPDSS_VER_OMAP4 131 
#define  OMAPDSS_VER_OMAP4430_ES1 130 
#define  OMAPDSS_VER_OMAP4430_ES2 129 
#define  OMAPDSS_VER_OMAP5 128 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dsi_pll_ops ; 
 int /*<<< orphan*/  dss_omap4_hdmi_pll_hw ; 
 int /*<<< orphan*/  dss_omap5_hdmi_pll_hw ; 
 int dss_pll_register (struct dss_pll*) ; 
 int omapdss_get_version () ; 

__attribute__((used)) static int dsi_init_pll_data(struct platform_device *pdev, struct hdmi_pll_data *hpll)
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

	switch (omapdss_get_version()) {
	case OMAPDSS_VER_OMAP4430_ES1:
	case OMAPDSS_VER_OMAP4430_ES2:
	case OMAPDSS_VER_OMAP4:
		pll->hw = &dss_omap4_hdmi_pll_hw;
		break;

	case OMAPDSS_VER_OMAP5:
	case OMAPDSS_VER_DRA7xx:
		pll->hw = &dss_omap5_hdmi_pll_hw;
		break;

	default:
		return -ENODEV;
	}

	pll->ops = &dsi_pll_ops;

	r = dss_pll_register(pll);
	if (r)
		return r;

	return 0;
}