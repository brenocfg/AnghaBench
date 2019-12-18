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
typedef  int uint32_t ;
struct drm_device {scalar_t__ switch_power_state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amdgpu_device {int flags; struct drm_device* ddev; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mclk ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PP_SENSOR_GFX_MCLK ; 
 int AMD_IS_PX ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_dpm_read_sensor (struct amdgpu_device*,int /*<<< orphan*/ ,void*,int*) ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_show_mclk(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	struct drm_device *ddev = adev->ddev;
	uint32_t mclk;
	int r, size = sizeof(mclk);

	/* Can't get voltage when the card is off */
	if  ((adev->flags & AMD_IS_PX) &&
	     (ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return -EINVAL;

	/* get the sclk */
	r = amdgpu_dpm_read_sensor(adev, AMDGPU_PP_SENSOR_GFX_MCLK,
				   (void *)&mclk, &size);
	if (r)
		return r;

	return snprintf(buf, PAGE_SIZE, "%d\n", mclk * 10 * 1000);
}