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
struct regmap {int dummy; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/  name; } ;
struct clk_hw {struct clk_init_data* init; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,struct clk_hw*) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  of_clk_parent_fill (struct device_node*,char const**,int) ; 
 int /*<<< orphan*/  of_get_parent (struct device_node*) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_sama5d2_clk_audio_pll_setup(struct device_node *np,
					  struct clk_init_data *init,
					  struct clk_hw *hw,
					  struct regmap **clk_audio_regmap)
{
	struct regmap *regmap;
	const char *parent_names[1];
	int ret;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	init->name = np->name;
	of_clk_parent_fill(np, parent_names, 1);
	init->parent_names = parent_names;
	init->num_parents = 1;

	hw->init = init;
	*clk_audio_regmap = regmap;

	ret = clk_hw_register(NULL, hw);
	if (ret)
		return ret;

	return of_clk_add_hw_provider(np, of_clk_hw_simple_get, hw);
}