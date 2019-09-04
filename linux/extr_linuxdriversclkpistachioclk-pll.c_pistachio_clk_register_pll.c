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
struct pistachio_pll {size_t id; int /*<<< orphan*/  nr_rates; int /*<<< orphan*/  rates; int /*<<< orphan*/  type; scalar_t__ reg_base; int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct clk** clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; scalar_t__ base; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* pll_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pistachio_clk_register_pll(struct pistachio_clk_provider *p,
				struct pistachio_pll *pll,
				unsigned int num)
{
	struct clk *clk;
	unsigned int i;

	for (i = 0; i < num; i++) {
		clk = pll_register(pll[i].name, pll[i].parent,
				   0, p->base + pll[i].reg_base,
				   pll[i].type, pll[i].rates,
				   pll[i].nr_rates);
		p->clk_data.clks[pll[i].id] = clk;
	}
}