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
struct mlxreg_hotplug_priv_data {TYPE_1__* hwmon; } ;
struct TYPE_4__ {int /*<<< orphan*/ * adapter; int /*<<< orphan*/ * client; } ;
struct mlxreg_core_data {TYPE_2__ hpdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxreg_hotplug_device_destroy(struct mlxreg_hotplug_priv_data *priv,
			      struct mlxreg_core_data *data)
{
	/* Notify user by sending hwmon uevent. */
	kobject_uevent(&priv->hwmon->kobj, KOBJ_CHANGE);

	if (data->hpdev.client) {
		i2c_unregister_device(data->hpdev.client);
		data->hpdev.client = NULL;
	}

	if (data->hpdev.adapter) {
		i2c_put_adapter(data->hpdev.adapter);
		data->hpdev.adapter = NULL;
	}
}