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
typedef  size_t uint32_t ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {scalar_t__ set_power_profile_mode; } ;

/* Variables and functions */
 size_t EINVAL ; 
 long PP_SMC_POWER_PROFILE_CUSTOM ; 
 int amdgpu_dpm_set_power_profile_mode (struct amdgpu_device*,long*,size_t) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 scalar_t__ isspace (char const) ; 
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int smu_set_power_profile_mode (int /*<<< orphan*/ *,long*,size_t) ; 
 char* strsep (char**,char const*) ; 

__attribute__((used)) static ssize_t amdgpu_set_pp_power_profile_mode(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	int ret = 0xff;
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	uint32_t parameter_size = 0;
	long parameter[64];
	char *sub_str, buf_cpy[128];
	char *tmp_str;
	uint32_t i = 0;
	char tmp[2];
	long int profile_mode = 0;
	const char delimiter[3] = {' ', '\n', '\0'};

	tmp[0] = *(buf);
	tmp[1] = '\0';
	ret = kstrtol(tmp, 0, &profile_mode);
	if (ret)
		goto fail;

	if (profile_mode == PP_SMC_POWER_PROFILE_CUSTOM) {
		if (count < 2 || count > 127)
			return -EINVAL;
		while (isspace(*++buf))
			i++;
		memcpy(buf_cpy, buf, count-i);
		tmp_str = buf_cpy;
		while (tmp_str[0]) {
			sub_str = strsep(&tmp_str, delimiter);
			ret = kstrtol(sub_str, 0, &parameter[parameter_size]);
			if (ret) {
				count = -EINVAL;
				goto fail;
			}
			parameter_size++;
			while (isspace(*tmp_str))
				tmp_str++;
		}
	}
	parameter[parameter_size] = profile_mode;
	if (is_support_sw_smu(adev))
		ret = smu_set_power_profile_mode(&adev->smu, parameter, parameter_size);
	else if (adev->powerplay.pp_funcs->set_power_profile_mode)
		ret = amdgpu_dpm_set_power_profile_mode(adev, parameter, parameter_size);
	if (!ret)
		return count;
fail:
	return -EINVAL;
}