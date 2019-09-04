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
struct pistachio_gate {size_t id; int /*<<< orphan*/  shift; scalar_t__ reg; int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct clk** clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; scalar_t__ base; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 struct clk* clk_register_gate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pistachio_clk_register_gate(struct pistachio_clk_provider *p,
				 struct pistachio_gate *gate,
				 unsigned int num)
{
	struct clk *clk;
	unsigned int i;

	for (i = 0; i < num; i++) {
		clk = clk_register_gate(NULL, gate[i].name, gate[i].parent,
					CLK_SET_RATE_PARENT,
					p->base + gate[i].reg, gate[i].shift,
					0, NULL);
		p->clk_data.clks[gate[i].id] = clk;
	}
}