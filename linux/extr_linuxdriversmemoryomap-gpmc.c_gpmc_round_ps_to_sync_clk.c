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
 int gpmc_calc_divider (int) ; 
 int gpmc_ps_to_ticks (int) ; 
 int gpmc_ticks_to_ps (int) ; 

__attribute__((used)) static u32 gpmc_round_ps_to_sync_clk(u32 time_ps, u32 sync_clk)
{
	u32 temp;
	int div;

	div = gpmc_calc_divider(sync_clk);
	temp = gpmc_ps_to_ticks(time_ps);
	temp = (temp + div - 1) / div;
	return gpmc_ticks_to_ps(temp * div);
}