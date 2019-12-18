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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int name; } ;
struct cpts {int /*<<< orphan*/  dev; TYPE_1__* reg; } ;
struct clk_hw {int name; } ;
struct TYPE_2__ {int /*<<< orphan*/  rftclk_sel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device_node*) ; 
 int PTR_ERR (struct device_node*) ; 
 struct device_node* clk_hw_register_mux_table (int /*<<< orphan*/ ,int,char const**,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_hw_unregister_mux ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ ,void (*) (void*),struct device_node*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,struct device_node*) ; 
 scalar_t__ of_clk_del_provider ; 
 unsigned int of_clk_get_parent_count (struct device_node*) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  of_clk_parent_fill (struct device_node*,char const**,unsigned int) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_variable_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int cpts_of_mux_clk_setup(struct cpts *cpts, struct device_node *node)
{
	struct device_node *refclk_np;
	const char **parent_names;
	unsigned int num_parents;
	struct clk_hw *clk_hw;
	int ret = -EINVAL;
	u32 *mux_table;

	refclk_np = of_get_child_by_name(node, "cpts-refclk-mux");
	if (!refclk_np)
		/* refclk selection supported not for all SoCs */
		return 0;

	num_parents = of_clk_get_parent_count(refclk_np);
	if (num_parents < 1) {
		dev_err(cpts->dev, "mux-clock %s must have parents\n",
			refclk_np->name);
		goto mux_fail;
	}

	parent_names = devm_kzalloc(cpts->dev, (sizeof(char *) * num_parents),
				    GFP_KERNEL);

	mux_table = devm_kzalloc(cpts->dev, sizeof(*mux_table) * num_parents,
				 GFP_KERNEL);
	if (!mux_table || !parent_names) {
		ret = -ENOMEM;
		goto mux_fail;
	}

	of_clk_parent_fill(refclk_np, parent_names, num_parents);

	ret = of_property_read_variable_u32_array(refclk_np, "ti,mux-tbl",
						  mux_table,
						  num_parents, num_parents);
	if (ret < 0)
		goto mux_fail;

	clk_hw = clk_hw_register_mux_table(cpts->dev, refclk_np->name,
					   parent_names, num_parents,
					   0,
					   &cpts->reg->rftclk_sel, 0, 0x1F,
					   0, mux_table, NULL);
	if (IS_ERR(clk_hw)) {
		ret = PTR_ERR(clk_hw);
		goto mux_fail;
	}

	ret = devm_add_action_or_reset(cpts->dev,
				       (void(*)(void *))clk_hw_unregister_mux,
				       clk_hw);
	if (ret) {
		dev_err(cpts->dev, "add clkmux unreg action %d", ret);
		goto mux_fail;
	}

	ret = of_clk_add_hw_provider(refclk_np, of_clk_hw_simple_get, clk_hw);
	if (ret)
		goto mux_fail;

	ret = devm_add_action_or_reset(cpts->dev,
				       (void(*)(void *))of_clk_del_provider,
				       refclk_np);
	if (ret) {
		dev_err(cpts->dev, "add clkmux provider unreg action %d", ret);
		goto mux_fail;
	}

	return ret;

mux_fail:
	of_node_put(refclk_np);
	return ret;
}