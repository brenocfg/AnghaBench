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
struct drm_device {int dummy; } ;

/* Variables and functions */

int
nouveau_hwmon_init(struct drm_device *dev)
{
#if defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvkm_iccsense *iccsense = nvxx_iccsense(&drm->client.device);
	struct nvkm_therm *therm = nvxx_therm(&drm->client.device);
	struct nvkm_volt *volt = nvxx_volt(&drm->client.device);
	const struct attribute_group *special_groups[N_ATTR_GROUPS];
	struct nouveau_hwmon *hwmon;
	struct device *hwmon_dev;
	int ret = 0;
	int i = 0;

	if (!iccsense && !therm && !volt) {
		NV_DEBUG(drm, "Skipping hwmon registration\n");
		return 0;
	}

	hwmon = drm->hwmon = kzalloc(sizeof(*hwmon), GFP_KERNEL);
	if (!hwmon)
		return -ENOMEM;
	hwmon->dev = dev;

	if (therm && therm->attr_get && therm->attr_set) {
		if (nvkm_therm_temp_get(therm) >= 0)
			special_groups[i++] = &temp1_auto_point_sensor_group;
		if (therm->fan_get && therm->fan_get(therm) >= 0)
			special_groups[i++] = &pwm_fan_sensor_group;
	}

	special_groups[i] = 0;
	hwmon_dev = hwmon_device_register_with_info(dev->dev, "nouveau", dev,
							&nouveau_chip_info,
							special_groups);
	if (IS_ERR(hwmon_dev)) {
		ret = PTR_ERR(hwmon_dev);
		NV_ERROR(drm, "Unable to register hwmon device: %d\n", ret);
		return ret;
	}

	hwmon->hwmon = hwmon_dev;
	return 0;
#else
	return 0;
#endif
}