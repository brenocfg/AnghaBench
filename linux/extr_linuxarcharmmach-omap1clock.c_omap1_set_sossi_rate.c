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
struct clk {unsigned long rate; TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MOD_CONF_CTRL_1 ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 

int omap1_set_sossi_rate(struct clk *clk, unsigned long rate)
{
	u32 l;
	int div;
	unsigned long p_rate;

	p_rate = clk->parent->rate;
	/* Round towards slower frequency */
	div = (p_rate + rate - 1) / rate;
	div--;
	if (div < 0 || div > 7)
		return -EINVAL;

	l = omap_readl(MOD_CONF_CTRL_1);
	l &= ~(7 << 17);
	l |= div << 17;
	omap_writel(l, MOD_CONF_CTRL_1);

	clk->rate = p_rate / (div + 1);

	return 0;
}