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
struct tegra_sor {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct tegra_clk_sor_pad {TYPE_1__ hw; struct tegra_sor* sor; } ;
struct clk_init_data {char const* name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; scalar_t__ flags; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct clk* devm_clk_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct tegra_clk_sor_pad* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_clk_sor_pad_ops ; 
 int /*<<< orphan*/  tegra_clk_sor_pad_parents ; 

__attribute__((used)) static struct clk *tegra_clk_sor_pad_register(struct tegra_sor *sor,
					      const char *name)
{
	struct tegra_clk_sor_pad *pad;
	struct clk_init_data init;
	struct clk *clk;

	pad = devm_kzalloc(sor->dev, sizeof(*pad), GFP_KERNEL);
	if (!pad)
		return ERR_PTR(-ENOMEM);

	pad->sor = sor;

	init.name = name;
	init.flags = 0;
	init.parent_names = tegra_clk_sor_pad_parents;
	init.num_parents = ARRAY_SIZE(tegra_clk_sor_pad_parents);
	init.ops = &tegra_clk_sor_pad_ops;

	pad->hw.init = &init;

	clk = devm_clk_register(sor->dev, &pad->hw);

	return clk;
}