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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct max2175 {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int MAX2175_IS_BAND_VHF (struct max2175*) ; 
 scalar_t__ MAX2175_IS_FMHD_MODE (struct max2175*) ; 
 scalar_t__ MAX2175_IS_FM_MODE (struct max2175*) ; 
 scalar_t__ MAX2175_LO_ABOVE_DESIRED ; 
 int max2175_set_lo_freq (struct max2175*,int) ; 
 int max2175_set_nco_freq (struct max2175*,int) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*) ; 

__attribute__((used)) static int max2175_set_rf_freq_non_am_bands(struct max2175 *ctx, u64 freq,
					    u32 lo_pos)
{
	s64 adj_freq, low_if_freq;
	int ret;

	mxm_dbg(ctx, "rf_freq: non AM bands\n");

	if (MAX2175_IS_FM_MODE(ctx))
		low_if_freq = 128000;
	else if (MAX2175_IS_FMHD_MODE(ctx))
		low_if_freq = 228000;
	else
		return max2175_set_lo_freq(ctx, freq);

	if (MAX2175_IS_BAND_VHF(ctx) == (lo_pos == MAX2175_LO_ABOVE_DESIRED))
		adj_freq = freq + low_if_freq;
	else
		adj_freq = freq - low_if_freq;

	ret = max2175_set_lo_freq(ctx, adj_freq);
	if (ret)
		return ret;

	return max2175_set_nco_freq(ctx, -low_if_freq);
}