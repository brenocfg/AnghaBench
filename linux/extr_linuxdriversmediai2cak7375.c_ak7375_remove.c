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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak7375_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ak7375_subdev_cleanup (struct ak7375_device*) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 struct ak7375_device* sd_to_ak7375_vcm (struct v4l2_subdev*) ; 

__attribute__((used)) static int ak7375_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct ak7375_device *ak7375_dev = sd_to_ak7375_vcm(sd);

	ak7375_subdev_cleanup(ak7375_dev);
	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);

	return 0;
}