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
struct clk {int flags; int enable_bit; int /*<<< orphan*/ * enable_reg; } ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int ENABLE_REG_32BIT ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int __raw_readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap1_clk_disable_generic(struct clk *clk)
{
	__u16 regval16;
	__u32 regval32;

	if (clk->enable_reg == NULL)
		return;

	if (clk->flags & ENABLE_REG_32BIT) {
		regval32 = __raw_readl(clk->enable_reg);
		regval32 &= ~(1 << clk->enable_bit);
		__raw_writel(regval32, clk->enable_reg);
	} else {
		regval16 = __raw_readw(clk->enable_reg);
		regval16 &= ~(1 << clk->enable_bit);
		__raw_writew(regval16, clk->enable_reg);
	}
}