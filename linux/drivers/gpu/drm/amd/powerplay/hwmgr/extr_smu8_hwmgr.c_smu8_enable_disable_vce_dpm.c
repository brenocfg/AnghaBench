#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct smu8_hwmgr {int /*<<< orphan*/  dpm_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMFlags_VCE_Enabled ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEDPM ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableAllSmuFeatures ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableAllSmuFeatures ; 
 int /*<<< orphan*/  VCE_DPM_MASK ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_enable_disable_vce_dpm(struct pp_hwmgr *hwmgr, bool enable)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	uint32_t dpm_features = 0;

	if (enable && phm_cap_enabled(
				hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_VCEDPM)) {
		data->dpm_flags |= DPMFlags_VCE_Enabled;
		dpm_features |= VCE_DPM_MASK;
		smum_send_msg_to_smc_with_parameter(hwmgr,
			    PPSMC_MSG_EnableAllSmuFeatures, dpm_features);
	} else {
		dpm_features |= VCE_DPM_MASK;
		data->dpm_flags &= ~DPMFlags_VCE_Enabled;
		smum_send_msg_to_smc_with_parameter(hwmgr,
			   PPSMC_MSG_DisableAllSmuFeatures, dpm_features);
	}

	return 0;
}