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
struct mxl111sf_demod_state {int dummy; } ;
typedef  enum fe_guard_interval { ____Placeholder_fe_guard_interval } fe_guard_interval ;

/* Variables and functions */
 int GUARD_INTERVAL_1_16 ; 
 int GUARD_INTERVAL_1_32 ; 
 int GUARD_INTERVAL_1_4 ; 
 int GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  V6_CP_TPS_REG ; 
 int V6_PARAM_GI_MASK ; 
 int mxl111sf_demod_read_reg (struct mxl111sf_demod_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static
int mxl1x1sf_demod_get_tps_guard_interval(struct mxl111sf_demod_state *state,
					  enum fe_guard_interval *guard)
{
	u8 val;
	int ret = mxl111sf_demod_read_reg(state, V6_CP_TPS_REG, &val);
	/* 00:1/32, 01:1/16, 10:1/8, 11:1/4 */
	if (mxl_fail(ret))
		goto fail;

	switch ((val & V6_PARAM_GI_MASK) >> 4) {
	case 0:
		*guard = GUARD_INTERVAL_1_32;
		break;
	case 1:
		*guard = GUARD_INTERVAL_1_16;
		break;
	case 2:
		*guard = GUARD_INTERVAL_1_8;
		break;
	case 3:
		*guard = GUARD_INTERVAL_1_4;
		break;
	}
fail:
	return ret;
}