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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct clk_init_data {char const* name; unsigned long flags; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_apb_mul {TYPE_1__ hw; int /*<<< orphan*/  bit_idx; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_apb_mul_factor_ops ; 
 struct clk* clk_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct clk_apb_mul*) ; 
 struct clk_apb_mul* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *clk_register_apb_mul(struct device *dev, const char *name,
					const char *parent_name,
					unsigned long flags, u8 bit_idx)
{
	struct clk_apb_mul *am;
	struct clk_init_data init;
	struct clk *clk;

	am = kzalloc(sizeof(*am), GFP_KERNEL);
	if (!am)
		return ERR_PTR(-ENOMEM);

	am->bit_idx = bit_idx;
	am->hw.init = &init;

	init.name = name;
	init.ops = &clk_apb_mul_factor_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_register(dev, &am->hw);

	if (IS_ERR(clk))
		kfree(am);

	return clk;
}