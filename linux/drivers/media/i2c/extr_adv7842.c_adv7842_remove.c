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
struct adv7842_state {int /*<<< orphan*/  delayed_work_enable_hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv7842_irq_enable (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  adv7842_unregister_clients (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7842_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct adv7842_state *state = to_state(sd);

	adv7842_irq_enable(sd, false);
	cancel_delayed_work(&state->delayed_work_enable_hotplug);
	v4l2_device_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);
	adv7842_unregister_clients(sd);
	v4l2_ctrl_handler_free(sd->ctrl_handler);
	return 0;
}