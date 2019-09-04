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
typedef  int /*<<< orphan*/  value ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ read_sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PP_SENSOR_GPU_LOAD ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_dpm_read_sensor (struct amdgpu_device*,int /*<<< orphan*/ ,void*,int*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t amdgpu_get_busy_percent(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	int r, value, size = sizeof(value);

	/* sanity check PP is enabled */
	if (!(adev->powerplay.pp_funcs &&
	      adev->powerplay.pp_funcs->read_sensor))
		return -EINVAL;

	/* read the IP busy sensor */
	r = amdgpu_dpm_read_sensor(adev, AMDGPU_PP_SENSOR_GPU_LOAD,
				   (void *)&value, &size);
	if (r)
		return r;

	return snprintf(buf, PAGE_SIZE, "%d\n", value);
}