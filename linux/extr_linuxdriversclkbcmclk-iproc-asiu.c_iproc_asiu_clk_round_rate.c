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
 unsigned int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 long EINVAL ; 

__attribute__((used)) static long iproc_asiu_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long *parent_rate)
{
	unsigned int div;

	if (rate == 0 || *parent_rate == 0)
		return -EINVAL;

	if (rate == *parent_rate)
		return *parent_rate;

	div = DIV_ROUND_UP(*parent_rate, rate);
	if (div < 2)
		return *parent_rate;

	return *parent_rate / div;
}