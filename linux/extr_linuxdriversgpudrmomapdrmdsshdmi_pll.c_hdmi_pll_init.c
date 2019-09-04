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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdmi_wp_data {int dummy; } ;
struct hdmi_pll_data {int /*<<< orphan*/  base; struct hdmi_wp_data* wp; struct platform_device* pdev; } ;
struct dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int hdmi_init_pll_data (struct dss_device*,struct platform_device*,struct hdmi_pll_data*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int hdmi_pll_init(struct dss_device *dss, struct platform_device *pdev,
		  struct hdmi_pll_data *pll, struct hdmi_wp_data *wp)
{
	int r;
	struct resource *res;

	pll->pdev = pdev;
	pll->wp = wp;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pll");
	pll->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pll->base))
		return PTR_ERR(pll->base);

	r = hdmi_init_pll_data(dss, pdev, pll);
	if (r) {
		DSSERR("failed to init HDMI PLL\n");
		return r;
	}

	return 0;
}