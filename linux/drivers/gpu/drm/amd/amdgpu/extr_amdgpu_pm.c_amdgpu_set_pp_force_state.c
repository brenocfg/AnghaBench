#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pp_states_info {int* states; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int pp_force_state_enabled; TYPE_2__ powerplay; } ;
typedef  size_t ssize_t ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;
struct TYPE_3__ {scalar_t__ get_pp_num_states; scalar_t__ dispatch_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PP_TASK_ENABLE_USER_STATE ; 
 unsigned long ARRAY_SIZE (int*) ; 
 size_t EINVAL ; 
 int POWER_STATE_TYPE_DEFAULT ; 
 int POWER_STATE_TYPE_INTERNAL_BOOT ; 
 int /*<<< orphan*/  amdgpu_dpm_dispatch_task (struct amdgpu_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  amdgpu_dpm_get_pp_num_states (struct amdgpu_device*,struct pp_states_info*) ; 
 unsigned long array_index_nospec (unsigned long,unsigned long) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static ssize_t amdgpu_set_pp_force_state(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	enum amd_pm_state_type state = 0;
	unsigned long idx;
	int ret;

	if (strlen(buf) == 1)
		adev->pp_force_state_enabled = false;
	else if (is_support_sw_smu(adev))
		adev->pp_force_state_enabled = false;
	else if (adev->powerplay.pp_funcs->dispatch_tasks &&
			adev->powerplay.pp_funcs->get_pp_num_states) {
		struct pp_states_info data;

		ret = kstrtoul(buf, 0, &idx);
		if (ret || idx >= ARRAY_SIZE(data.states)) {
			count = -EINVAL;
			goto fail;
		}
		idx = array_index_nospec(idx, ARRAY_SIZE(data.states));

		amdgpu_dpm_get_pp_num_states(adev, &data);
		state = data.states[idx];
		/* only set user selected power states */
		if (state != POWER_STATE_TYPE_INTERNAL_BOOT &&
		    state != POWER_STATE_TYPE_DEFAULT) {
			amdgpu_dpm_dispatch_task(adev,
					AMD_PP_TASK_ENABLE_USER_STATE, &state);
			adev->pp_force_state_enabled = true;
		}
	}
fail:
	return count;
}