#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct clk_init_data {char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/  name; int /*<<< orphan*/  ops; } ;
struct TYPE_3__ {struct clk_init_data* init; } ;
struct clk_creg_data {TYPE_1__ hw; struct regmap* reg; int /*<<< orphan*/  name; int /*<<< orphan*/  ops; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 

__attribute__((used)) static struct clk *clk_register_creg_clk(struct device *dev,
					 struct clk_creg_data *creg_clk,
					 const char **parent_name,
					 struct regmap *syscon)
{
	struct clk_init_data init;

	init.ops = creg_clk->ops;
	init.name = creg_clk->name;
	init.parent_names = parent_name;
	init.num_parents = 1;
	init.flags = 0;

	creg_clk->reg = syscon;
	creg_clk->hw.init = &init;

	if (dev)
		return devm_clk_register(dev, &creg_clk->hw);

	return clk_register(NULL, &creg_clk->hw);
}