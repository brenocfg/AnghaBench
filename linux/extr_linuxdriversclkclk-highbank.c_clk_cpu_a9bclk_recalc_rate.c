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
struct hb_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int HB_A9_BCLK_DIV_MASK ; 
 int HB_A9_BCLK_DIV_SHIFT ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct hb_clk* to_hb_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_cpu_a9bclk_recalc_rate(struct clk_hw *hwclk,
						unsigned long parent_rate)
{
	struct hb_clk *hbclk = to_hb_clk(hwclk);
	u32 div = (readl(hbclk->reg) & HB_A9_BCLK_DIV_MASK) >> HB_A9_BCLK_DIV_SHIFT;

	return parent_rate / (div + 2);
}