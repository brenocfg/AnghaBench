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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  entity; } ;
struct i2c_client {int dummy; } ;
struct adv76xx_state {int /*<<< orphan*/  delayed_work_enable_hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv76xx_unregister_clients (struct adv76xx_state*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv76xx_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct adv76xx_state *state = to_state(sd);

	/* disable interrupts */
	io_write(sd, 0x40, 0);
	io_write(sd, 0x41, 0);
	io_write(sd, 0x46, 0);
	io_write(sd, 0x6e, 0);
	io_write(sd, 0x73, 0);

	cancel_delayed_work(&state->delayed_work_enable_hotplug);
	v4l2_async_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);
	adv76xx_unregister_clients(to_state(sd));
	v4l2_ctrl_handler_free(sd->ctrl_handler);
	return 0;
}