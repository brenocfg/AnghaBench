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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CLK_DIRECT ; 
 scalar_t__ CLK_MAX ; 
 scalar_t__ DIRECT_IF_44MHZ ; 
 scalar_t__ DIRECT_IF_57MHZ ; 
 scalar_t__ LOW_IF_4MHZ ; 

__attribute__((used)) static bool mn88443x_t_is_valid_clk(u32 adckt, u32 if_freq)
{
	if (if_freq == DIRECT_IF_57MHZ) {
		if (adckt >= CLK_DIRECT && adckt <= 21000000)
			return true;
		if (adckt >= 25300000 && adckt <= CLK_MAX)
			return true;
	} else if (if_freq == DIRECT_IF_44MHZ) {
		if (adckt >= 25000000 && adckt <= CLK_MAX)
			return true;
	} else if (if_freq >= LOW_IF_4MHZ && if_freq < DIRECT_IF_44MHZ) {
		if (adckt >= CLK_DIRECT && adckt <= CLK_MAX)
			return true;
	}

	return false;
}