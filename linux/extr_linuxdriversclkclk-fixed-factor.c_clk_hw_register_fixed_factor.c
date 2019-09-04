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
struct clk_init_data {char const* name; unsigned long flags; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct clk_fixed_factor {unsigned int mult; unsigned int div; struct clk_hw hw; } ;

/* Variables and functions */
 unsigned long CLK_IS_BASIC ; 
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clk_fixed_factor_ops ; 
 int clk_hw_register (struct device*,struct clk_hw*) ; 
 int /*<<< orphan*/  kfree (struct clk_fixed_factor*) ; 
 struct clk_fixed_factor* kmalloc (int,int /*<<< orphan*/ ) ; 

struct clk_hw *clk_hw_register_fixed_factor(struct device *dev,
		const char *name, const char *parent_name, unsigned long flags,
		unsigned int mult, unsigned int div)
{
	struct clk_fixed_factor *fix;
	struct clk_init_data init;
	struct clk_hw *hw;
	int ret;

	fix = kmalloc(sizeof(*fix), GFP_KERNEL);
	if (!fix)
		return ERR_PTR(-ENOMEM);

	/* struct clk_fixed_factor assignments */
	fix->mult = mult;
	fix->div = div;
	fix->hw.init = &init;

	init.name = name;
	init.ops = &clk_fixed_factor_ops;
	init.flags = flags | CLK_IS_BASIC;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	hw = &fix->hw;
	ret = clk_hw_register(dev, hw);
	if (ret) {
		kfree(fix);
		hw = ERR_PTR(ret);
	}

	return hw;
}