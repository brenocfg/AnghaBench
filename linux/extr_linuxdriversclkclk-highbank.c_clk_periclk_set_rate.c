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
 int EINVAL ; 
 struct hb_clk* to_hb_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_periclk_set_rate(struct clk_hw *hwclk, unsigned long rate,
				unsigned long parent_rate)
{
	struct hb_clk *hbclk = to_hb_clk(hwclk);
	u32 div;

	div = parent_rate / rate;
	if (div & 0x1)
		return -EINVAL;

	writel(div >> 1, hbclk->reg);
	return 0;
}