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
typedef  int u8 ;
typedef  void* u16 ;
struct device {int dummy; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_sysctrl {int* reg_bits; int* reg_mask; unsigned long rate; unsigned long enable_delay_us; TYPE_1__ hw; struct device* dev; scalar_t__ parent_index; void** reg_sel; } ;
struct clk_ops {int dummy; } ;
struct clk_init_data {char const* name; unsigned long flags; char const** parent_names; int num_parents; struct clk_ops const* ops; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int SYSCTRL_MAX_NUM_PARENTS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 struct clk_sysctrl* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *clk_reg_sysctrl(struct device *dev,
				const char *name,
				const char **parent_names,
				u8 num_parents,
				u16 *reg_sel,
				u8 *reg_mask,
				u8 *reg_bits,
				unsigned long rate,
				unsigned long enable_delay_us,
				unsigned long flags,
				const struct clk_ops *clk_sysctrl_ops)
{
	struct clk_sysctrl *clk;
	struct clk_init_data clk_sysctrl_init;
	struct clk *clk_reg;
	int i;

	if (!dev)
		return ERR_PTR(-EINVAL);

	if (!name || (num_parents > SYSCTRL_MAX_NUM_PARENTS)) {
		dev_err(dev, "clk_sysctrl: invalid arguments passed\n");
		return ERR_PTR(-EINVAL);
	}

	clk = devm_kzalloc(dev, sizeof(*clk), GFP_KERNEL);
	if (!clk)
		return ERR_PTR(-ENOMEM);

	/* set main clock registers */
	clk->reg_sel[0] = reg_sel[0];
	clk->reg_bits[0] = reg_bits[0];
	clk->reg_mask[0] = reg_mask[0];

	/* handle clocks with more than one parent */
	for (i = 1; i < num_parents; i++) {
		clk->reg_sel[i] = reg_sel[i];
		clk->reg_bits[i] = reg_bits[i];
		clk->reg_mask[i] = reg_mask[i];
	}

	clk->parent_index = 0;
	clk->rate = rate;
	clk->enable_delay_us = enable_delay_us;
	clk->dev = dev;

	clk_sysctrl_init.name = name;
	clk_sysctrl_init.ops = clk_sysctrl_ops;
	clk_sysctrl_init.flags = flags;
	clk_sysctrl_init.parent_names = parent_names;
	clk_sysctrl_init.num_parents = num_parents;
	clk->hw.init = &clk_sysctrl_init;

	clk_reg = devm_clk_register(clk->dev, &clk->hw);
	if (IS_ERR(clk_reg))
		dev_err(dev, "clk_sysctrl: clk_register failed\n");

	return clk_reg;
}