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
struct pistachio_div {size_t id; int /*<<< orphan*/  div_flags; int /*<<< orphan*/  width; scalar_t__ reg; int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct clk** clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; scalar_t__ base; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_register_divider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pistachio_clk_register_div(struct pistachio_clk_provider *p,
				struct pistachio_div *div,
				unsigned int num)
{
	struct clk *clk;
	unsigned int i;

	for (i = 0; i < num; i++) {
		clk = clk_register_divider(NULL, div[i].name, div[i].parent,
					   0, p->base + div[i].reg, 0,
					   div[i].width, div[i].div_flags,
					   NULL);
		p->clk_data.clks[div[i].id] = clk;
	}
}