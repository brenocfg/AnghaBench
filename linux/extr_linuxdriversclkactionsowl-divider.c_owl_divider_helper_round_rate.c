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
struct owl_divider_hw {int /*<<< orphan*/  div_flags; int /*<<< orphan*/  width; int /*<<< orphan*/  table; } ;
struct owl_clk_common {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 long divider_round_rate (int /*<<< orphan*/ *,unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

long owl_divider_helper_round_rate(struct owl_clk_common *common,
				const struct owl_divider_hw *div_hw,
				unsigned long rate,
				unsigned long *parent_rate)
{
	return divider_round_rate(&common->hw, rate, parent_rate,
				  div_hw->table, div_hw->width,
				  div_hw->div_flags);
}