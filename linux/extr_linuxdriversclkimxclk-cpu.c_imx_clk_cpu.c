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
struct clk_init_data {char const* name; char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_cpu {TYPE_1__ hw; struct clk* step; struct clk* pll; struct clk* mux; struct clk* div; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_cpu_ops ; 
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct clk_cpu*) ; 
 struct clk_cpu* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk *imx_clk_cpu(const char *name, const char *parent_name,
		struct clk *div, struct clk *mux, struct clk *pll,
		struct clk *step)
{
	struct clk_cpu *cpu;
	struct clk *clk;
	struct clk_init_data init;

	cpu = kzalloc(sizeof(*cpu), GFP_KERNEL);
	if (!cpu)
		return ERR_PTR(-ENOMEM);

	cpu->div = div;
	cpu->mux = mux;
	cpu->pll = pll;
	cpu->step = step;

	init.name = name;
	init.ops = &clk_cpu_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	cpu->hw.init = &init;

	clk = clk_register(NULL, &cpu->hw);
	if (IS_ERR(clk))
		kfree(cpu);

	return clk;
}