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
 unsigned long gpmc_get_fclk_period () ; 
 unsigned long gpmc_ps_to_ticks (unsigned int) ; 

__attribute__((used)) static unsigned int gpmc_round_ps_to_ticks(unsigned int time_ps)
{
	unsigned long ticks = gpmc_ps_to_ticks(time_ps);

	return ticks * gpmc_get_fclk_period();
}