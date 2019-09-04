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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int vega12_get_gpu_power(struct pp_hwmgr *hwmgr, uint32_t *query)
{
#if 0
	uint32_t value;

	PP_ASSERT_WITH_CODE(!smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetCurrPkgPwr),
			"Failed to get current package power!",
			return -EINVAL);

	value = smum_get_argument(hwmgr);
	/* power value is an integer */
	*query = value << 8;
#endif
	return 0;
}