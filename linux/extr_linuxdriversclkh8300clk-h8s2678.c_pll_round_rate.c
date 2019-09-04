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
 unsigned long MAX_FREQ ; 
 unsigned long MIN_FREQ ; 
 long abs (unsigned long) ; 

__attribute__((used)) static long pll_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	int i, m = -1;
	long offset[3];

	if (rate > MAX_FREQ)
		rate = MAX_FREQ;
	if (rate < MIN_FREQ)
		rate = MIN_FREQ;

	for (i = 0; i < 3; i++)
		offset[i] = abs(rate - (*prate * (1 << i)));
	for (i = 0; i < 3; i++)
		if (m < 0)
			m = i;
		else
			m = (offset[i] < offset[m])?i:m;

	return *prate * (1 << m);
}