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
struct clk {int flags; int /*<<< orphan*/  usecount; struct clk* parent; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable ) (struct clk*) ;} ;

/* Variables and functions */
 int CLOCK_NO_IDLE_PARENT ; 
 int /*<<< orphan*/  omap1_clk_deny_idle (struct clk*) ; 
 int /*<<< orphan*/  omap1_clk_disable (struct clk*) ; 
 int stub1 (struct clk*) ; 

int omap1_clk_enable(struct clk *clk)
{
	int ret = 0;

	if (clk->usecount++ == 0) {
		if (clk->parent) {
			ret = omap1_clk_enable(clk->parent);
			if (ret)
				goto err;

			if (clk->flags & CLOCK_NO_IDLE_PARENT)
				omap1_clk_deny_idle(clk->parent);
		}

		ret = clk->ops->enable(clk);
		if (ret) {
			if (clk->parent)
				omap1_clk_disable(clk->parent);
			goto err;
		}
	}
	return ret;

err:
	clk->usecount--;
	return ret;
}