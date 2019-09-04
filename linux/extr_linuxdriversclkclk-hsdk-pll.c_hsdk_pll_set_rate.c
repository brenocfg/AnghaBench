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
struct hsdk_pll_clk {int /*<<< orphan*/  dev; TYPE_1__* pll_devdata; } ;
struct hsdk_pll_cfg {unsigned long rate; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* update_rate ) (struct hsdk_pll_clk*,unsigned long,struct hsdk_pll_cfg const*) ;struct hsdk_pll_cfg* pll_cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int stub1 (struct hsdk_pll_clk*,unsigned long,struct hsdk_pll_cfg const*) ; 
 struct hsdk_pll_clk* to_hsdk_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static int hsdk_pll_set_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long parent_rate)
{
	int i;
	struct hsdk_pll_clk *clk = to_hsdk_pll_clk(hw);
	const struct hsdk_pll_cfg *pll_cfg = clk->pll_devdata->pll_cfg;

	for (i = 0; pll_cfg[i].rate != 0; i++) {
		if (pll_cfg[i].rate == rate) {
			return clk->pll_devdata->update_rate(clk, rate,
							     &pll_cfg[i]);
		}
	}

	dev_err(clk->dev, "invalid rate=%ld, parent_rate=%ld\n", rate,
			parent_rate);

	return -EINVAL;
}