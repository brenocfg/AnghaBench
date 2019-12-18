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
struct imx_pgc_domain {int num_clks; struct clk** clk; TYPE_1__* dev; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPC_CLK_MAX ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct clk* of_clk_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imx_pgc_get_clocks(struct imx_pgc_domain *domain)
{
	int i, ret;

	for (i = 0; ; i++) {
		struct clk *clk = of_clk_get(domain->dev->of_node, i);
		if (IS_ERR(clk))
			break;
		if (i >= GPC_CLK_MAX) {
			dev_err(domain->dev, "more than %d clocks\n",
				GPC_CLK_MAX);
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