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
struct tda1997x_platform_data {scalar_t__ audout_format; } ;
struct tda1997x_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  page_lock; int /*<<< orphan*/  delayed_work_enable_hpd; int /*<<< orphan*/  supplies; int /*<<< orphan*/  hdl; TYPE_1__* client; int /*<<< orphan*/  audio_lock; struct tda1997x_platform_data pdata; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDA1997X_NUM_SUPPLIES ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tda1997x_state*) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda1997x_power_mode (struct tda1997x_state*,int /*<<< orphan*/ ) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tda1997x_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct tda1997x_state *state = to_state(sd);
	struct tda1997x_platform_data *pdata = &state->pdata;

	if (pdata->audout_format) {
		mutex_destroy(&state->audio_lock);
	}

	disable_irq(state->client->irq);
	tda1997x_power_mode(state, 0);

	v4l2_async_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_free(&state->hdl);
	regulator_bulk_disable(TDA1997X_NUM_SUPPLIES, state->supplies);
	cancel_delayed_work(&state->delayed_work_enable_hpd);
	mutex_destroy(&state->page_lock);
	mutex_destroy(&state->lock);

	kfree(state);

	return 0;
}