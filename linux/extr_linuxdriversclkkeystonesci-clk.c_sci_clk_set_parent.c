#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sci_clk {scalar_t__ clk_id; int /*<<< orphan*/  dev_id; TYPE_2__* provider; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sci; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_parent ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct sci_clk* to_sci_clk (struct clk_hw*) ; 

__attribute__((used)) static int sci_clk_set_parent(struct clk_hw *hw, u8 index)
{
	struct sci_clk *clk = to_sci_clk(hw);

	return clk->provider->ops->set_parent(clk->provider->sci, clk->dev_id,
					      clk->clk_id,
					      index + 1 + clk->clk_id);
}