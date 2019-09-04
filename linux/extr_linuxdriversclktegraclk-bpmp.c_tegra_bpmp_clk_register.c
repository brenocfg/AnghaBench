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
struct tegra_bpmp_clk_info {unsigned int num_parents; char* name; int flags; int /*<<< orphan*/  id; int /*<<< orphan*/ * parents; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct tegra_bpmp_clk {unsigned int num_parents; TYPE_1__ hw; int /*<<< orphan*/ * parents; struct tegra_bpmp* bpmp; int /*<<< orphan*/  id; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; } ;
struct clk_init_data {char* name; unsigned int num_parents; char const** parent_names; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  init ;

/* Variables and functions */
 int ENOMEM ; 
 struct tegra_bpmp_clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TEGRA_BPMP_CLK_HAS_MUX ; 
 int TEGRA_BPMP_CLK_HAS_SET_RATE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_clk_hw_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct tegra_bpmp_clk* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const**) ; 
 int /*<<< orphan*/  memset (struct clk_init_data*,int /*<<< orphan*/ ,int) ; 
 struct tegra_bpmp_clk_info* tegra_bpmp_clk_find (struct tegra_bpmp_clk_info const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_bpmp_clk_gate_ops ; 
 int /*<<< orphan*/  tegra_bpmp_clk_mux_ops ; 
 int /*<<< orphan*/  tegra_bpmp_clk_mux_rate_ops ; 
 int /*<<< orphan*/  tegra_bpmp_clk_rate_ops ; 

__attribute__((used)) static struct tegra_bpmp_clk *
tegra_bpmp_clk_register(struct tegra_bpmp *bpmp,
			const struct tegra_bpmp_clk_info *info,
			const struct tegra_bpmp_clk_info *clocks,
			unsigned int num_clocks)
{
	struct tegra_bpmp_clk *clk;
	struct clk_init_data init;
	const char **parents;
	unsigned int i;
	int err;

	clk = devm_kzalloc(bpmp->dev, sizeof(*clk), GFP_KERNEL);
	if (!clk)
		return ERR_PTR(-ENOMEM);

	clk->id = info->id;
	clk->bpmp = bpmp;

	clk->parents = devm_kcalloc(bpmp->dev, info->num_parents,
				    sizeof(*clk->parents), GFP_KERNEL);
	if (!clk->parents)
		return ERR_PTR(-ENOMEM);

	clk->num_parents = info->num_parents;

	/* hardware clock initialization */
	memset(&init, 0, sizeof(init));
	init.name = info->name;
	clk->hw.init = &init;

	if (info->flags & TEGRA_BPMP_CLK_HAS_MUX) {
		if (info->flags & TEGRA_BPMP_CLK_HAS_SET_RATE)
			init.ops = &tegra_bpmp_clk_mux_rate_ops;
		else
			init.ops = &tegra_bpmp_clk_mux_ops;
	} else {
		if (info->flags & TEGRA_BPMP_CLK_HAS_SET_RATE)
			init.ops = &tegra_bpmp_clk_rate_ops;
		else
			init.ops = &tegra_bpmp_clk_gate_ops;
	}

	init.num_parents = info->num_parents;

	parents = kcalloc(info->num_parents, sizeof(*parents), GFP_KERNEL);
	if (!parents)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < info->num_parents; i++) {
		const struct tegra_bpmp_clk_info *parent;

		/* keep a private copy of the ID to parent index map */
		clk->parents[i] = info->parents[i];

		parent = tegra_bpmp_clk_find(clocks, num_clocks,
					     info->parents[i]);
		if (!parent) {
			dev_err(bpmp->dev, "no parent %u found for %u\n",
				info->parents[i], info->id);
			continue;
		}

		parents[i] = parent->name;
	}

	init.parent_names = parents;

	err = devm_clk_hw_register(bpmp->dev, &clk->hw);

	kfree(parents);

	if (err < 0)
		return ERR_PTR(err);

	return clk;
}