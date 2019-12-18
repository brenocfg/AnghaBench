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
struct pp_states_info {int nums; scalar_t__* states; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ get_pp_num_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ POWER_STATE_TYPE_BALANCED ; 
 scalar_t__ POWER_STATE_TYPE_BATTERY ; 
 scalar_t__ POWER_STATE_TYPE_INTERNAL_BOOT ; 
 scalar_t__ POWER_STATE_TYPE_PERFORMANCE ; 
 int /*<<< orphan*/  amdgpu_dpm_get_pp_num_states (struct amdgpu_device*,struct pp_states_info*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_get_power_num_states (int /*<<< orphan*/ *,struct pp_states_info*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static ssize_t amdgpu_get_pp_num_states(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	struct pp_states_info data;
	int i, buf_len, ret;

	if (is_support_sw_smu(adev)) {
		ret = smu_get_power_num_states(&adev->smu, &data);
		if (ret)
			return ret;
	} else if (adev->powerplay.pp_funcs->get_pp_num_states)
		amdgpu_dpm_get_pp_num_states(adev, &data);

	buf_len = snprintf(buf, PAGE_SIZE, "states: %d\n", data.nums);
	for (i = 0; i < data.nums; i++)
		buf_len += snprintf(buf + buf_len, PAGE_SIZE, "%d %s\n", i,
				(data.states[i] == POWER_STATE_TYPE_INTERNAL_BOOT) ? "boot" :
				(data.states[i] == POWER_STATE_TYPE_BATTERY) ? "battery" :
				(data.states[i] == POWER_STATE_TYPE_BALANCED) ? "balanced" :
				(data.states[i] == POWER_STATE_TYPE_PERFORMANCE) ? "performance" : "default");

	return buf_len;
}