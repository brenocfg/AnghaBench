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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {scalar_t__ set_ppfeature_status; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int amdgpu_dpm_set_ppfeature_status (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int kstrtou64 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int smu_sys_set_pp_feature_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t amdgpu_set_pp_feature_status(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	uint64_t featuremask;
	int ret;

	ret = kstrtou64(buf, 0, &featuremask);
	if (ret)
		return -EINVAL;

	pr_debug("featuremask = 0x%llx\n", featuremask);

	if (is_support_sw_smu(adev)) {
		ret = smu_sys_set_pp_feature_mask(&adev->smu, featuremask);
		if (ret)
			return -EINVAL;
	} else if (adev->powerplay.pp_funcs->set_ppfeature_status) {
		ret = amdgpu_dpm_set_ppfeature_status(adev, featuremask);
		if (ret)
			return -EINVAL;
	}

	return count;
}