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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct adv7180_state {scalar_t__ irq; int /*<<< orphan*/  mutex; int /*<<< orphan*/  csi_client; int /*<<< orphan*/  vpp_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv7180_exit_controls (struct adv7180_state*) ; 
 int /*<<< orphan*/  adv7180_set_power_pin (struct adv7180_state*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adv7180_state*) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7180_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct adv7180_state *state = to_state(sd);

	v4l2_async_unregister_subdev(sd);

	if (state->irq > 0)
		free_irq(client->irq, state);

	media_entity_cleanup(&sd->entity);
	adv7180_exit_controls(state);

	i2c_unregister_device(state->vpp_client);
	i2c_unregister_device(state->csi_client);

	adv7180_set_power_pin(state, false);

	mutex_destroy(&state->mutex);

	return 0;
}