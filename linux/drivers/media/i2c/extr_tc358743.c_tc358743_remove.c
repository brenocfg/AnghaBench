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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct tc358743_state {int /*<<< orphan*/  hdl; int /*<<< orphan*/  confctl_mutex; int /*<<< orphan*/  cec_adap; int /*<<< orphan*/  delayed_work_enable_hotplug; int /*<<< orphan*/  work_i2c_poll; int /*<<< orphan*/  timer; TYPE_1__* i2c_client; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct tc358743_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int tc358743_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct tc358743_state *state = to_state(sd);

	if (!state->i2c_client->irq) {
		del_timer_sync(&state->timer);
		flush_work(&state->work_i2c_poll);
	}
	cancel_delayed_work(&state->delayed_work_enable_hotplug);
	cec_unregister_adapter(state->cec_adap);
	v4l2_async_unregister_subdev(sd);
	v4l2_device_unregister_subdev(sd);
	mutex_destroy(&state->confctl_mutex);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_free(&state->hdl);

	return 0;
}