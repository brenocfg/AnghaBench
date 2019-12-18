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
struct nvkm_volt {int dummy; } ;
struct nvkm_therm {scalar_t__ (* fan_get ) (struct nvkm_therm*) ;scalar_t__ attr_set; scalar_t__ attr_get; } ;
struct nvkm_iccsense {int dummy; } ;
struct nouveau_hwmon {struct device* hwmon; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nouveau_drm {struct nouveau_hwmon* hwmon; TYPE_1__ client; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int N_ATTR_GROUPS ; 
 int PTR_ERR (struct device*) ; 
 struct device* hwmon_device_register_with_info (int /*<<< orphan*/ ,char*,struct drm_device*,int /*<<< orphan*/ *,struct attribute_group const**) ; 
 struct nouveau_hwmon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_chip_info ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nvkm_therm_temp_get (struct nvkm_therm*) ; 
 struct nvkm_iccsense* nvxx_iccsense (int /*<<< orphan*/ *) ; 
 struct nvkm_therm* nvxx_therm (int /*<<< orphan*/ *) ; 
 struct nvkm_volt* nvxx_volt (int /*<<< orphan*/ *) ; 
 struct attribute_group pwm_fan_sensor_group ; 
 scalar_t__ stub1 (struct nvkm_therm*) ; 
 struct attribute_group temp1_auto_point_sensor_group ; 

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