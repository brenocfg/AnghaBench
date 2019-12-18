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

__attribute__((used)) static inline u32 rv6xx_calculate_spread_spectrum_clk_v(u32 vco_freq, u32 ref_freq,
							u32 ss_rate, u32 ss_percent,
							u32 fb_divider_scale)
{
	u32 fb_divider = vco_freq / ref_freq;

	return (ss_percent * ss_rate * 4 * (fb_divider * fb_divider) /
		(5375 * ((vco_freq * 10) / (4096 >> fb_divider_scale))));
}