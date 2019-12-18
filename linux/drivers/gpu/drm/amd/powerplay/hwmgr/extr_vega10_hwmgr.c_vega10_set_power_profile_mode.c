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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct vega10_hwmgr {int* custom_profile_mode; } ;
struct pp_hwmgr {size_t power_profile_mode; struct vega10_hwmgr* backend; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_SetCustomGfxDpmParameters ; 
 int /*<<< orphan*/  PPSMC_MSG_SetWorkloadMask ; 
 size_t PP_SMC_POWER_PROFILE_CUSTOM ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vega10_set_power_profile_mode(struct pp_hwmgr *hwmgr, long *input, uint32_t size)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	uint8_t busy_set_point;
	uint8_t FPS;
	uint8_t use_rlc_busy;
	uint8_t min_active_level;
	uint32_t power_profile_mode = input[size];

	if (power_profile_mode == PP_SMC_POWER_PROFILE_CUSTOM) {
		if (size != 0 && size != 4)
			return -EINVAL;

		/* If size = 0 and the CUSTOM profile has been set already
		 * then just apply the profile. The copy stored in the hwmgr
		 * is zeroed out on init
		 */
		if (size == 0) {
			if (data->custom_profile_mode[0] != 0)
				goto out;
			else
				return -EINVAL;
		}

		data->custom_profile_mode[0] = busy_set_point = input[0];
		data->custom_profile_mode[1] = FPS = input[1];
		data->custom_profile_mode[2] = use_rlc_busy = input[2];
		data->custom_profile_mode[3] = min_active_level = input[3];
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetCustomGfxDpmParameters,
					busy_set_point | FPS<<8 |
					use_rlc_busy << 16 | min_active_level<<24);
	}

out:
	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_SetWorkloadMask,
						1 << power_profile_mode);
	hwmgr->power_profile_mode = power_profile_mode;

	return 0;
}