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
struct i2c_client {int dummy; } ;
struct adv7393_state {int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 struct adv7393_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7393_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct adv7393_state *state = to_state(sd);

	v4l2_device_unregister_subdev(sd);
	v4l2_ctrl_handler_free(&state->hdl);

	return 0;
}