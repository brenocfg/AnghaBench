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
struct i2c_adapter {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector_funcs {int dummy; } ;
struct drm_connector {struct i2c_adapter* ddc; } ;

/* Variables and functions */
 int drm_connector_init (struct drm_device*,struct drm_connector*,struct drm_connector_funcs const*,int) ; 

int drm_connector_init_with_ddc(struct drm_device *dev,
				struct drm_connector *connector,
				const struct drm_connector_funcs *funcs,
				int connector_type,
				struct i2c_adapter *ddc)
{
	int ret;

	ret = drm_connector_init(dev, connector, funcs, connector_type);
	if (ret)
		return ret;

	/* provide ddc symlink in sysfs */
	connector->ddc = ddc;

	return ret;
}