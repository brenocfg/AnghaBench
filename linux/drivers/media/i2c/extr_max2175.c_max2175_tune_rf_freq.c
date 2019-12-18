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
struct max2175 {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX2175_BUFFER_PLUS_PRESET_TUNE ; 
 int max2175_csm_action (struct max2175*,int /*<<< orphan*/ ) ; 
 int max2175_set_rf_freq (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2175_tune_rf_freq(struct max2175 *ctx, u64 freq, u32 hsls)
{
	int ret;

	ret = max2175_set_rf_freq(ctx, freq, hsls);
	if (ret)
		return ret;

	ret = max2175_csm_action(ctx, MAX2175_BUFFER_PLUS_PRESET_TUNE);
	if (ret)
		return ret;

	mxm_dbg(ctx, "tune_rf_freq: old %u new %llu\n", ctx->freq, freq);
	ctx->freq = freq;

	return ret;
}