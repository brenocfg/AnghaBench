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
struct dw9807_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw9807_subdev_cleanup (struct dw9807_device*) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct dw9807_device* sd_to_dw9807_vcm (struct v4l2_subdev*) ; 

__attribute__((used)) static int dw9807_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct dw9807_device *dw9807_dev = sd_to_dw9807_vcm(sd);

	pm_runtime_disable(&client->dev);

	dw9807_subdev_cleanup(dw9807_dev);

	return 0;
}