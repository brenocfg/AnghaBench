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
typedef  size_t uint32_t ;
struct profile_mode_setting {long bupdate_sclk; long bupdate_mclk; long sclk_up_hyst; long sclk_down_hyst; long sclk_activity; long mclk_up_hyst; long mclk_down_hyst; long mclk_activity; } ;
struct smu7_hwmgr {struct profile_mode_setting current_profile_setting; } ;
struct pp_hwmgr {int power_profile_mode; scalar_t__ backend; } ;
typedef  enum PP_SMC_POWER_PROFILE { ____Placeholder_PP_SMC_POWER_PROFILE } PP_SMC_POWER_PROFILE ;

/* Variables and functions */
 int EINVAL ; 
#define  PP_SMC_POWER_PROFILE_COMPUTE 133 
#define  PP_SMC_POWER_PROFILE_CUSTOM 132 
#define  PP_SMC_POWER_PROFILE_FULLSCREEN3D 131 
#define  PP_SMC_POWER_PROFILE_POWERSAVING 130 
#define  PP_SMC_POWER_PROFILE_VIDEO 129 
#define  PP_SMC_POWER_PROFILE_VR 128 
 int /*<<< orphan*/  memcpy (struct profile_mode_setting*,struct profile_mode_setting*,int) ; 
 int /*<<< orphan*/  smu7_patch_compute_profile_mode (struct pp_hwmgr*,int) ; 
 struct profile_mode_setting* smu7_profiling ; 
 int /*<<< orphan*/  smum_update_dpm_settings (struct pp_hwmgr*,struct profile_mode_setting*) ; 

__attribute__((used)) static int smu7_set_power_profile_mode(struct pp_hwmgr *hwmgr, long *input, uint32_t size)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct profile_mode_setting tmp;
	enum PP_SMC_POWER_PROFILE mode;

	if (input == NULL)
		return -EINVAL;

	mode = input[size];
	switch (mode) {
	case PP_SMC_POWER_PROFILE_CUSTOM:
		if (size < 8 && size != 0)
			return -EINVAL;
		/* If only CUSTOM is passed in, use the saved values. Check
		 * that we actually have a CUSTOM profile by ensuring that
		 * the "use sclk" or the "use mclk" bits are set
		 */
		tmp = smu7_profiling[PP_SMC_POWER_PROFILE_CUSTOM];
		if (size == 0) {
			if (tmp.bupdate_sclk == 0 && tmp.bupdate_mclk == 0)
				return -EINVAL;
		} else {
			tmp.bupdate_sclk = input[0];
			tmp.sclk_up_hyst = input[1];
			tmp.sclk_down_hyst = input[2];
			tmp.sclk_activity = input[3];
			tmp.bupdate_mclk = input[4];
			tmp.mclk_up_hyst = input[5];
			tmp.mclk_down_hyst = input[6];
			tmp.mclk_activity = input[7];
			smu7_profiling[PP_SMC_POWER_PROFILE_CUSTOM] = tmp;
		}
		if (!smum_update_dpm_settings(hwmgr, &tmp)) {
			memcpy(&data->current_profile_setting, &tmp, sizeof(struct profile_mode_setting));
			hwmgr->power_profile_mode = mode;
		}
		break;
	case PP_SMC_POWER_PROFILE_FULLSCREEN3D:
	case PP_SMC_POWER_PROFILE_POWERSAVING:
	case PP_SMC_POWER_PROFILE_VIDEO:
	case PP_SMC_POWER_PROFILE_VR:
	case PP_SMC_POWER_PROFILE_COMPUTE:
		if (mode == hwmgr->power_profile_mode)
			return 0;

		memcpy(&tmp, &smu7_profiling[mode], sizeof(struct profile_mode_setting));
		if (!smum_update_dpm_settings(hwmgr, &tmp)) {
			if (tmp.bupdate_sclk) {
				data->current_profile_setting.bupdate_sclk = tmp.bupdate_sclk;
				data->current_profile_setting.sclk_up_hyst = tmp.sclk_up_hyst;
				data->current_profile_setting.sclk_down_hyst = tmp.sclk_down_hyst;
				data->current_profile_setting.sclk_activity = tmp.sclk_activity;
			}
			if (tmp.bupdate_mclk) {
				data->current_profile_setting.bupdate_mclk = tmp.bupdate_mclk;
				data->current_profile_setting.mclk_up_hyst = tmp.mclk_up_hyst;
				data->current_profile_setting.mclk_down_hyst = tmp.mclk_down_hyst;
				data->current_profile_setting.mclk_activity = tmp.mclk_activity;
			}
			smu7_patch_compute_profile_mode(hwmgr, mode);
			hwmgr->power_profile_mode = mode;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}