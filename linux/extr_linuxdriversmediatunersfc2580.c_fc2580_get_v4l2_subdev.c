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
struct v4l2_subdev {scalar_t__ ops; } ;
struct i2c_client {int dummy; } ;
struct fc2580_dev {struct v4l2_subdev subdev; } ;

/* Variables and functions */
 struct fc2580_dev* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static struct v4l2_subdev *fc2580_get_v4l2_subdev(struct i2c_client *client)
{
	struct fc2580_dev *dev = i2c_get_clientdata(client);

	if (dev->subdev.ops)
		return &dev->subdev;
	else
		return NULL;
}