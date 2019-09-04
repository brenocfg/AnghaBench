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
typedef  unsigned long u32 ;
struct hb_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int HB_A9_PCLK_DIV ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct hb_clk* to_hb_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_cpu_periphclk_recalc_rate(struct clk_hw *hwclk,
						   unsigned long parent_rate)
{
	struct hb_clk *hbclk = to_hb_clk(hwclk);
	u32 div = (readl(hbclk->reg) & HB_A9_PCLK_DIV) ? 8 : 4;
	return parent_rate / div;
}