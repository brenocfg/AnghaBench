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
typedef  int /*<<< orphan*/  temp ;
struct drm_device {scalar_t__ switch_power_state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amdgpu_device {int flags; struct drm_device* ddev; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PP_SENSOR_EDGE_TEMP ; 
 int /*<<< orphan*/  AMDGPU_PP_SENSOR_HOTSPOT_TEMP ; 
 int /*<<< orphan*/  AMDGPU_PP_SENSOR_MEM_TEMP ; 
 int AMD_IS_PX ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  PP_TEMP_EDGE 130 
#define  PP_TEMP_JUNCTION 129 
 int PP_TEMP_MAX ; 
#define  PP_TEMP_MEM 128 
 int amdgpu_dpm_read_sensor (struct amdgpu_device*,int /*<<< orphan*/ ,void*,int*) ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_show_temp(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	struct drm_device *ddev = adev->ddev;
	int channel = to_sensor_dev_attr(attr)->index;
	int r, temp = 0, size = sizeof(temp);

	/* Can't get temperature when the card is off */
	if  ((adev->flags & AMD_IS_PX) &&
	     (ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return -EINVAL;

	if (channel >= PP_TEMP_MAX)
		return -EINVAL;

	switch (channel) {
	case PP_TEMP_JUNCTION:
		/* get current junction temperature */
		r = amdgpu_dpm_read_sensor(adev, AMDGPU_PP_SENSOR_HOTSPOT_TEMP,
					   (void *)&temp, &size);
		if (r)
			return r;
		break;
	case PP_TEMP_EDGE:
		/* get current edge temperature */
		r = amdgpu_dpm_read_sensor(adev, AMDGPU_PP_SENSOR_EDGE_TEMP,
					   (void *)&temp, &size);
		if (r)
			return r;
		break;
	case PP_TEMP_MEM:
		/* get current memory temperature */
		r = amdgpu_dpm_read_sensor(adev, AMDGPU_PP_SENSOR_MEM_TEMP,
					   (void *)&temp, &size);
		if (r)
			return r;
		break;
	}

	return snprintf(buf, PAGE_SIZE, "%d\n", temp);
}