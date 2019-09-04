#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
struct clk_hw {struct clk_init_data* init; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  axg_clk_no_ops ; 
 int devm_clk_hw_register (struct device*,struct clk_hw*) ; 
 struct clk_hw* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static struct clk_hw *axg_clk_hw_register_bypass(struct device *dev,
						 const char *name,
						 const char *parent_name)
{
	struct clk_hw *hw;
	struct clk_init_data init;
	char *clk_name;
	int ret;

	hw = devm_kzalloc(dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return ERR_PTR(-ENOMEM);

	clk_name = kasprintf(GFP_KERNEL, "axg_%s", name);
	if (!clk_name)
		return ERR_PTR(-ENOMEM);

	init.name = clk_name;
	init.ops = &axg_clk_no_ops;
	init.flags = 0;
	init.parent_names = parent_name ? &parent_name : NULL;
	init.num_parents = parent_name ? 1 : 0;
	hw->init = &init;

	ret = devm_clk_hw_register(dev, hw);
	kfree(clk_name);

	return ret ? ERR_PTR(ret) : hw;
}