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

/* Variables and functions */
 int gpmc_ps_to_ticks (unsigned int) ; 

int gpmc_calc_divider(unsigned int sync_clk)
{
	int div = gpmc_ps_to_ticks(sync_clk);

	if (div > 4)
		return -1;
	if (div <= 0)
		div = 1;

	return div;
}