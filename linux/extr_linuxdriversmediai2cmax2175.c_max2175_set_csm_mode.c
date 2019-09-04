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
struct max2175 {int dummy; } ;
typedef  enum max2175_csm_mode { ____Placeholder_max2175_csm_mode } max2175_csm_mode ;

/* Variables and functions */
#define  MAX2175_PRESET_TUNE 128 
 int max2175_poll_csm_ready (struct max2175*) ; 
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool max2175_set_csm_mode(struct max2175 *ctx,
			  enum max2175_csm_mode new_mode)
{
	int ret = max2175_poll_csm_ready(ctx);

	if (ret)
		return ret;

	max2175_write_bits(ctx, 0, 2, 0, new_mode);
	mxm_dbg(ctx, "set csm new mode %d\n", new_mode);

	/* Wait for a fixed settle down time depending on new mode */
	switch (new_mode) {
	case MAX2175_PRESET_TUNE:
		usleep_range(51100, 51500);	/* 51.1ms */
		break;
	/*
	 * Other mode switches need different sleep values depending on band &
	 * mode
	 */
	default:
		break;
	}

	return max2175_poll_csm_ready(ctx);
}