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
struct clk_hw {TYPE_1__* core; } ;
struct clk {char const* dev_id; int /*<<< orphan*/  clks_node; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  con_id; TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_CAST (struct clk_hw*) ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct clk_hw*) ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 struct clk* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk *__clk_create_clk(struct clk_hw *hw, const char *dev_id,
			     const char *con_id)
{
	struct clk *clk;

	/* This is to allow this function to be chained to others */
	if (IS_ERR_OR_NULL(hw))
		return ERR_CAST(hw);

	clk = kzalloc(sizeof(*clk), GFP_KERNEL);
	if (!clk)
		return ERR_PTR(-ENOMEM);

	clk->core = hw->core;
	clk->dev_id = dev_id;
	clk->con_id = kstrdup_const(con_id, GFP_KERNEL);
	clk->max_rate = ULONG_MAX;

	clk_prepare_lock();
	hlist_add_head(&clk->clks_node, &hw->core->clks);
	clk_prepare_unlock();

	return clk;
}