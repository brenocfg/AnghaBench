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
struct pistachio_fixed_factor {size_t id; int /*<<< orphan*/  div; int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct clk** clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_register_fixed_factor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void pistachio_clk_register_fixed_factor(struct pistachio_clk_provider *p,
					 struct pistachio_fixed_factor *ff,
					 unsigned int num)
{
	struct clk *clk;
	unsigned int i;

	for (i = 0; i < num; i++) {
		clk = clk_register_fixed_factor(NULL, ff[i].name, ff[i].parent,
						0, 1, ff[i].div);
		p->clk_data.clks[ff[i].id] = clk;
	}
}