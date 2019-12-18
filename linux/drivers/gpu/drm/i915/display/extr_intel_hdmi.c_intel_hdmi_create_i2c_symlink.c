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
struct kobject {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct kobject kobj; } ;
struct i2c_adapter {TYPE_1__ dev; } ;
struct drm_connector {TYPE_2__* kdev; } ;
struct TYPE_4__ {struct kobject kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct i2c_adapter* intel_hdmi_get_i2c_adapter (struct drm_connector*) ; 
 int sysfs_create_link (struct kobject*,struct kobject*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_hdmi_create_i2c_symlink(struct drm_connector *connector)
{
	struct i2c_adapter *adapter = intel_hdmi_get_i2c_adapter(connector);
	struct kobject *i2c_kobj = &adapter->dev.kobj;
	struct kobject *connector_kobj = &connector->kdev->kobj;
	int ret;

	ret = sysfs_create_link(connector_kobj, i2c_kobj, i2c_kobj->name);
	if (ret)
		DRM_ERROR("Failed to create i2c symlink (%d)\n", ret);
}