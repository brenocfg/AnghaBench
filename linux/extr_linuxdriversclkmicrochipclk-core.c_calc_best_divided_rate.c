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

/* Variables and functions */
 scalar_t__ abs (unsigned long) ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long calc_best_divided_rate(unsigned long rate,
					    unsigned long parent_rate,
					    u32 divider_max,
					    u32 divider_min)
{
	unsigned long divided_rate, divided_rate_down, best_rate;
	unsigned long div, div_up;

	/* eq. clk_rate = parent_rate / divider.
	 *
	 * Find best divider to produce closest of target divided rate.
	 */
	div = parent_rate / rate;
	div = clamp_val(div, divider_min, divider_max);
	div_up = clamp_val(div + 1, divider_min, divider_max);

	divided_rate = parent_rate / div;
	divided_rate_down = parent_rate / div_up;
	if (abs(rate - divided_rate_down) < abs(rate - divided_rate))
		best_rate = divided_rate_down;
	else
		best_rate = divided_rate;

	return best_rate;
}