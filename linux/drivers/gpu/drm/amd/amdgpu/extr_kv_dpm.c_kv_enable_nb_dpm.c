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
struct kv_power_info {int nb_dpm_enabled; scalar_t__ enable_nb_dpm; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_NBDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_NBDPM_Enable ; 
 int amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_enable_nb_dpm(struct amdgpu_device *adev,
			    bool enable)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	int ret = 0;

	if (enable) {
		if (pi->enable_nb_dpm && !pi->nb_dpm_enabled) {
			ret = amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_NBDPM_Enable);
			if (ret == 0)
				pi->nb_dpm_enabled = true;
		}
	} else {
		if (pi->enable_nb_dpm && pi->nb_dpm_enabled) {
			ret = amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_NBDPM_Disable);
			if (ret == 0)
				pi->nb_dpm_enabled = false;
		}
	}

	return ret;
}