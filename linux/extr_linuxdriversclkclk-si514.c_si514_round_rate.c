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
struct clk_si514_muldiv {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int si514_calc_muldiv (struct clk_si514_muldiv*,unsigned long) ; 
 long si514_calc_rate (struct clk_si514_muldiv*) ; 

__attribute__((used)) static long si514_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	struct clk_si514_muldiv settings;
	int err;

	if (!rate)
		return 0;

	err = si514_calc_muldiv(&settings, rate);
	if (err)
		return err;

	return si514_calc_rate(&settings);
}