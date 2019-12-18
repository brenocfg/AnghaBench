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
struct smu7_hwmgr {int power_containment_features; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int POWERCONTAINMENT_FEATURE_PkgPwrLimit ; 
 int /*<<< orphan*/  PPSMC_MSG_PkgPwrSetLimit ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

int smu7_set_power_limit(struct pp_hwmgr *hwmgr, uint32_t n)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (data->power_containment_features &
			POWERCONTAINMENT_FEATURE_PkgPwrLimit)
		return smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_PkgPwrSetLimit, n<<8);
	return 0;
}