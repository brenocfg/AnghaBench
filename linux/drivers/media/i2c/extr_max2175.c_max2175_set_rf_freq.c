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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct max2175 {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX2175_IS_BAND_AM (struct max2175*) ; 
 int max2175_set_nco_freq (struct max2175*,int /*<<< orphan*/ ) ; 
 int max2175_set_rf_freq_non_am_bands (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2175_set_rf_freq(struct max2175 *ctx, u64 freq, u32 lo_pos)
{
	int ret;

	if (MAX2175_IS_BAND_AM(ctx))
		ret = max2175_set_nco_freq(ctx, freq);
	else
		ret = max2175_set_rf_freq_non_am_bands(ctx, freq, lo_pos);

	mxm_dbg(ctx, "set_rf_freq: ret %d freq %llu\n", ret, freq);

	return ret;
}