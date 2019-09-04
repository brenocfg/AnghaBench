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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  roclk_calc_div_trim (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long roclk_calc_rate (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long roclk_round_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long *parent_rate)
{
	u32 rotrim, rodiv;

	/* calculate dividers for new rate */
	roclk_calc_div_trim(rate, *parent_rate, &rodiv, &rotrim);

	/* caclulate new rate (rounding) based on new rodiv & rotrim */
	return roclk_calc_rate(*parent_rate, rodiv, rotrim);
}