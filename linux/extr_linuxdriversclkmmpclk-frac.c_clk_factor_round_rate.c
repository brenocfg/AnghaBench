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
struct mmp_clk_factor {int ftbl_cnt; TYPE_2__* masks; TYPE_1__* ftbl; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {unsigned long factor; } ;
struct TYPE_3__ {unsigned long den; unsigned long num; } ;

/* Variables and functions */
 struct mmp_clk_factor* to_clk_factor (struct clk_hw*) ; 

__attribute__((used)) static long clk_factor_round_rate(struct clk_hw *hw, unsigned long drate,
		unsigned long *prate)
{
	struct mmp_clk_factor *factor = to_clk_factor(hw);
	unsigned long rate = 0, prev_rate;
	int i;

	for (i = 0; i < factor->ftbl_cnt; i++) {
		prev_rate = rate;
		rate = (((*prate / 10000) * factor->ftbl[i].den) /
			(factor->ftbl[i].num * factor->masks->factor)) * 10000;
		if (rate > drate)
			break;
	}
	if ((i == 0) || (i == factor->ftbl_cnt)) {
		return rate;
	} else {
		if ((drate - prev_rate) > (rate - drate))
			return rate;
		else
			return prev_rate;
	}
}