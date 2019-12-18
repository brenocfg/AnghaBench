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
typedef  int uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_GetCurrPkgPwr ; 
 int smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_get_gpu_power(struct pp_hwmgr *hwmgr,
		uint32_t *query)
{
	uint32_t value;

	if (!query)
		return -EINVAL;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrPkgPwr);
	value = smum_get_argument(hwmgr);

	/* SMC returning actual watts, keep consistent with legacy asics, low 8 bit as 8 fractional bits */
	*query = value << 8;

	return 0;
}