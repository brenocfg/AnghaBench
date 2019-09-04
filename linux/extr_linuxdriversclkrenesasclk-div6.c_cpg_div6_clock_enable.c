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
typedef  int u32 ;
struct div6_clock {int /*<<< orphan*/  reg; scalar_t__ div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CPG_DIV6_CKSTP ; 
 int CPG_DIV6_DIV (scalar_t__) ; 
 int CPG_DIV6_DIV_MASK ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct div6_clock* to_div6_clock (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpg_div6_clock_enable(struct clk_hw *hw)
{
	struct div6_clock *clock = to_div6_clock(hw);
	u32 val;

	val = (readl(clock->reg) & ~(CPG_DIV6_DIV_MASK | CPG_DIV6_CKSTP))
	    | CPG_DIV6_DIV(clock->div - 1);
	writel(val, clock->reg);

	return 0;
}