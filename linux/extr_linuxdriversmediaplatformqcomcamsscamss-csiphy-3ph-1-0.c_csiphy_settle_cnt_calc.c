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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int div_u64 (long long,int) ; 

__attribute__((used)) static u8 csiphy_settle_cnt_calc(u32 pixel_clock, u8 bpp, u8 num_lanes,
				 u32 timer_clk_rate)
{
	u32 mipi_clock; /* Hz */
	u32 ui; /* ps */
	u32 timer_period; /* ps */
	u32 t_hs_prepare_max; /* ps */
	u32 t_hs_settle; /* ps */
	u8 settle_cnt;

	mipi_clock = pixel_clock * bpp / (2 * num_lanes);
	ui = div_u64(1000000000000LL, mipi_clock);
	ui /= 2;
	t_hs_prepare_max = 85000 + 6 * ui;
	t_hs_settle = t_hs_prepare_max;

	timer_period = div_u64(1000000000000LL, timer_clk_rate);
	settle_cnt = t_hs_settle / timer_period - 6;

	return settle_cnt;
}