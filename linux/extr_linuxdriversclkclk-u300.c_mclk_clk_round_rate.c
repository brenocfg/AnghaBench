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
struct clk_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static long
mclk_clk_round_rate(struct clk_hw *hw, unsigned long rate,
		    unsigned long *prate)
{
	if (rate <= 18900000)
		return 18900000;
	if (rate <= 20800000)
		return 20800000;
	if (rate <= 23100000)
		return 23100000;
	if (rate <= 26000000)
		return 26000000;
	if (rate <= 29700000)
		return 29700000;
	if (rate <= 34700000)
		return 34700000;
	if (rate <= 41600000)
		return 41600000;
	/* Highest rate */
	return 52000000;
}