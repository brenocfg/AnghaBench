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
typedef  int u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static long clk_cpu_round_rate(struct clk_hw *hwclk, unsigned long rate,
			       unsigned long *parent_rate)
{
	/* Valid ratio are 1:1, 1:2 and 1:3 */
	u32 div;

	div = *parent_rate / rate;
	if (div == 0)
		div = 1;
	else if (div > 3)
		div = 3;

	return *parent_rate / div;
}