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

__attribute__((used)) static long clk_tve_di_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *prate)
{
	unsigned long div;

	div = *prate / rate;
	if (div >= 4)
		return *prate / 4;
	else if (div >= 2)
		return *prate / 2;
	return *prate;
}