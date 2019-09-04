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
struct tvp7002 {int /*<<< orphan*/  hdl; int /*<<< orphan*/  sd; } ;
struct i2c_client {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 struct tvp7002* to_tvp7002 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvp7002_remove(struct i2c_client *c)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(c);
	struct tvp7002 *device = to_tvp7002(sd);

	v4l2_dbg(1, debug, sd, "Removing tvp7002 adapter"
				"on address 0x%x\n", c->addr);
	v4l2_async_unregister_subdev(&device->sd);
#if defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&device->sd.entity);
#endif
	v4l2_ctrl_handler_free(&device->hdl);
	return 0;
}