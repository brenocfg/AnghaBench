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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char const*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,char const*,int) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* msm_clk_get (struct platform_device*,char const*) ; 

__attribute__((used)) static int get_clk(struct platform_device *pdev, struct clk **clkp,
		const char *name, bool mandatory)
{
	struct device *dev = &pdev->dev;
	struct clk *clk = msm_clk_get(pdev, name);
	if (IS_ERR(clk) && mandatory) {
		DRM_DEV_ERROR(dev, "failed to get %s (%ld)\n", name, PTR_ERR(clk));
		return PTR_ERR(clk);
	}
	if (IS_ERR(clk))
		DBG("skipping %s", name);
	else
		*clkp = clk;

	return 0;
}