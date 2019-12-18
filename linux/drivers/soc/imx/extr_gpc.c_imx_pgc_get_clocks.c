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
struct imx_pm_domain {int num_clks; struct clk** clk; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPC_CLK_MAX ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct clk* of_clk_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imx_pgc_get_clocks(struct device *dev, struct imx_pm_domain *domain)
{
	int i, ret;

	for (i = 0; ; i++) {
		struct clk *clk = of_clk_get(dev->of_node, i);
		if (IS_ERR(clk))
			break;
		if (i >= GPC_CLK_MAX) {
			dev_err(dev, "more than %d clocks\n", GPC_CLK_MAX);
			ret = -EINVAL;
			goto clk_err;
		}
		domain->clk[i] = clk;
	}
	domain->num_clks = i;

	return 0;

clk_err:
	while (i--)
		clk_put(domain->clk[i]);

	return ret;
}