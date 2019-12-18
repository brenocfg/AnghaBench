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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

void v4l2_i2c_subdev_unregister(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	/*
	 * We need to unregister the i2c client
	 * explicitly. We cannot rely on
	 * i2c_del_adapter to always unregister
	 * clients for us, since if the i2c bus is a
	 * platform bus, then it is never deleted.
	 *
	 * Device tree or ACPI based devices must not
	 * be unregistered as they have not been
	 * registered by us, and would not be
	 * re-created by just probing the V4L2 driver.
	 */
	if (client && !client->dev.of_node && !client->dev.fwnode)
		i2c_unregister_device(client);
}