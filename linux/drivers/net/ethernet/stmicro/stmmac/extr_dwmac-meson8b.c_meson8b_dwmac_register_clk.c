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
struct meson8b_dwmac {int /*<<< orphan*/  dev; } ;
struct clk_ops {int dummy; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; int /*<<< orphan*/  flags; struct clk_ops const* ops; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  clk_name ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 struct clk* devm_clk_register (int /*<<< orphan*/ ,struct clk_hw*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static struct clk *meson8b_dwmac_register_clk(struct meson8b_dwmac *dwmac,
					      const char *name_suffix,
					      const char **parent_names,
					      int num_parents,
					      const struct clk_ops *ops,
					      struct clk_hw *hw)
{
	struct clk_init_data init;
	char clk_name[32];

	snprintf(clk_name, sizeof(clk_name), "%s#%s", dev_name(dwmac->dev),
		 name_suffix);

	init.name = clk_name;
	init.ops = ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	hw->init = &init;

	return devm_clk_register(dwmac->dev, hw);
}