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
struct smu8_hwmgr {int is_nb_dpm_enabled; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 unsigned long NB_DPM_MASK ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableAllSmuFeatures ; 
 int /*<<< orphan*/  PP_DBG_LOG (char*) ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int smu8_enable_nb_dpm(struct pp_hwmgr *hwmgr)
{
	int ret = 0;

	struct smu8_hwmgr *data = hwmgr->backend;
	unsigned long dpm_features = 0;

	if (!data->is_nb_dpm_enabled) {
		PP_DBG_LOG("enabling ALL SMU features.\n");
		dpm_features |= NB_DPM_MASK;
		ret = smum_send_msg_to_smc_with_parameter(
							  hwmgr,
							  PPSMC_MSG_EnableAllSmuFeatures,
							  dpm_features);
		if (ret == 0)
			data->is_nb_dpm_enabled = true;
	}

	return ret;
}