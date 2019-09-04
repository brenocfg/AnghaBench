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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  reg; } ;
struct sd_clock {unsigned int div_num; unsigned int cur_div_idx; TYPE_2__ csn; TYPE_1__* div_table; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {unsigned int div; int val; } ;

/* Variables and functions */
 int CPG_SD_FC_MASK ; 
 int CPG_SD_STP_MASK ; 
 int EINVAL ; 
 unsigned int cpg_sd_clock_calc_div (struct sd_clock*,unsigned long,unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct sd_clock* to_sd_clock (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpg_sd_clock_set_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long parent_rate)
{
	struct sd_clock *clock = to_sd_clock(hw);
	unsigned int div = cpg_sd_clock_calc_div(clock, rate, parent_rate);
	u32 val;
	unsigned int i;

	for (i = 0; i < clock->div_num; i++)
		if (div == clock->div_table[i].div)
			break;

	if (i >= clock->div_num)
		return -EINVAL;

	clock->cur_div_idx = i;

	val = readl(clock->csn.reg);
	val &= ~(CPG_SD_STP_MASK | CPG_SD_FC_MASK);
	val |= clock->div_table[i].val & (CPG_SD_STP_MASK | CPG_SD_FC_MASK);
	writel(val, clock->csn.reg);

	return 0;
}