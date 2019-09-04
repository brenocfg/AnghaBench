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
typedef  int u32 ;
struct clk_omap_reg {int offset; } ;
struct clk_hw_omap {int enable_bit; int /*<<< orphan*/  enable_reg; } ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_2__ {int (* clk_readl ) (struct clk_omap_reg*) ;int /*<<< orphan*/  (* clk_writel ) (int,struct clk_omap_reg*) ;} ;

/* Variables and functions */
 int CM_AUTOIDLE ; 
 int CM_ICLKEN ; 
 int /*<<< orphan*/  memcpy (struct clk_omap_reg*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct clk_omap_reg*) ; 
 int /*<<< orphan*/  stub2 (int,struct clk_omap_reg*) ; 
 TYPE_1__* ti_clk_ll_ops ; 

void omap2_clkt_iclk_deny_idle(struct clk_hw_omap *clk)
{
	u32 v;
	struct clk_omap_reg r;

	memcpy(&r, &clk->enable_reg, sizeof(r));

	r.offset ^= (CM_AUTOIDLE ^ CM_ICLKEN);

	v = ti_clk_ll_ops->clk_readl(&r);
	v &= ~(1 << clk->enable_bit);
	ti_clk_ll_ops->clk_writel(v, &r);
}