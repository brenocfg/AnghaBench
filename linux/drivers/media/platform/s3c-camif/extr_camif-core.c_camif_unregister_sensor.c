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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {struct v4l2_subdev* sd; } ;
struct camif_dev {TYPE_1__ sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void camif_unregister_sensor(struct camif_dev *camif)
{
	struct v4l2_subdev *sd = camif->sensor.sd;
	struct i2c_client *client = sd ? v4l2_get_subdevdata(sd) : NULL;
	struct i2c_adapter *adapter;

	if (client == NULL)
		return;

	adapter = client->adapter;
	v4l2_device_unregister_subdev(sd);
	camif->sensor.sd = NULL;
	i2c_unregister_device(client);
	i2c_put_adapter(adapter);
}