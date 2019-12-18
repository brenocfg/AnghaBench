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

/* Variables and functions */
 int round_up (int,int) ; 

__attribute__((used)) static u32 calc_startup_ticks_9260(u32 startup_time, u32 adc_clk_khz)
{
	/*
	 * Number of ticks needed to cover the startup time of the ADC
	 * as defined in the electrical characteristics of the board,
	 * divided by 8. The formula thus is :
	 *   Startup Time = (ticks + 1) * 8 / ADC Clock
	 */
	return round_up((startup_time * adc_clk_khz / 1000) - 1, 8) / 8;
}