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
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_init_data {char const** parent_names; unsigned int num_parents; char const* name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct serdes_am654_clk_mux {unsigned int reg; int clk_id; TYPE_1__ hw; struct regmap* regmap; struct clk_init_data clk_data; } ;
struct serdes_am654 {struct regmap** clks; struct device* dev; struct device_node* of_node; } ;
struct regmap {int dummy; } ;
struct device_node {int /*<<< orphan*/  parent; } ;
struct device {int dummy; } ;
typedef  struct regmap clk ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_NO_REPARENT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct regmap* devm_clk_register (struct device*,TYPE_1__*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 unsigned int of_clk_get_parent_count (struct device_node*) ; 
 int /*<<< orphan*/  of_clk_parent_fill (struct device_node*,char const**,unsigned int) ; 
 int /*<<< orphan*/ * of_get_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdes_am654_clk_mux_ops ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serdes_am654_clk_register(struct serdes_am654 *am654_phy,
				     const char *clock_name, int clock_num)
{
	struct device_node *node = am654_phy->of_node;
	struct device *dev = am654_phy->dev;
	struct serdes_am654_clk_mux *mux;
	struct device_node *regmap_node;
	const char **parent_names;
	struct clk_init_data *init;
	unsigned int num_parents;
	struct regmap *regmap;
	const __be32 *addr;
	unsigned int reg;
	struct clk *clk;
	int ret = 0;

	mux = devm_kzalloc(dev, sizeof(*mux), GFP_KERNEL);
	if (!mux)
		return -ENOMEM;

	init = &mux->clk_data;

	regmap_node = of_parse_phandle(node, "ti,serdes-clk", 0);
	if (!regmap_node) {
		dev_err(dev, "Fail to get serdes-clk node\n");
		ret = -ENODEV;
		goto out_put_node;
	}

	regmap = syscon_node_to_regmap(regmap_node->parent);
	if (IS_ERR(regmap)) {
		dev_err(dev, "Fail to get Syscon regmap\n");
		ret = PTR_ERR(regmap);
		goto out_put_node;
	}

	num_parents = of_clk_get_parent_count(node);
	if (num_parents < 2) {
		dev_err(dev, "SERDES clock must have parents\n");
		ret = -EINVAL;
		goto out_put_node;
	}

	parent_names = devm_kzalloc(dev, (sizeof(char *) * num_parents),
				    GFP_KERNEL);
	if (!parent_names) {
		ret = -ENOMEM;
		goto out_put_node;
	}

	of_clk_parent_fill(node, parent_names, num_parents);

	addr = of_get_address(regmap_node, 0, NULL, NULL);
	if (!addr) {
		ret = -EINVAL;
		goto out_put_node;
	}

	reg = be32_to_cpu(*addr);

	init->ops = &serdes_am654_clk_mux_ops;
	init->flags = CLK_SET_RATE_NO_REPARENT;
	init->parent_names = parent_names;
	init->num_parents = num_parents;
	init->name = clock_name;

	mux->regmap = regmap;
	mux->reg = reg;
	mux->clk_id = clock_num;
	mux->hw.init = init;

	clk = devm_clk_register(dev, &mux->hw);
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		goto out_put_node;
	}

	am654_phy->clks[clock_num] = clk;

out_put_node:
	of_node_put(regmap_node);
	return ret;
}