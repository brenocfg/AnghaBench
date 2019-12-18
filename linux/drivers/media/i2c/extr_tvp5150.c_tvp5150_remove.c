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
struct v4l2_subdev {int /*<<< orphan*/  dev; } ;
struct tvp5150 {int /*<<< orphan*/  hdl; } ;
struct i2c_client {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tvp5150_remove(struct i2c_client *c)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(c);
	struct tvp5150 *decoder = to_tvp5150(sd);

	dev_dbg_lvl(sd->dev, 1, debug,
		"tvp5150.c: removing tvp5150 adapter on address 0x%x\n",
		c->addr << 1);

	v4l2_async_unregister_subdev(sd);
	v4l2_ctrl_handler_free(&decoder->hdl);
	return 0;
}