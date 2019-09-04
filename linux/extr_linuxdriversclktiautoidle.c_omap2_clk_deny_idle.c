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
struct clk_hw_omap {TYPE_1__* ops; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deny_idle ) (struct clk_hw_omap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_get_hw (struct clk*) ; 
 int /*<<< orphan*/  stub1 (struct clk_hw_omap*) ; 
 struct clk_hw_omap* to_clk_hw_omap (int /*<<< orphan*/ ) ; 

int omap2_clk_deny_idle(struct clk *clk)
{
	struct clk_hw_omap *c;

	c = to_clk_hw_omap(__clk_get_hw(clk));
	if (c->ops && c->ops->deny_idle)
		c->ops->deny_idle(c);
	return 0;
}