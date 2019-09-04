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

void
nouveau_hwmon_fini(struct drm_device *dev)
{
#if defined(CONFIG_HWMON) || (defined(MODULE) && defined(CONFIG_HWMON_MODULE))
	struct nouveau_hwmon *hwmon = nouveau_hwmon(dev);

	if (!hwmon)
		return;

	if (hwmon->hwmon)
		hwmon_device_unregister(hwmon->hwmon);

	nouveau_drm(dev)->hwmon = NULL;
	kfree(hwmon);
#endif
}