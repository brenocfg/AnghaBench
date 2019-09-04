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
struct msp_state {int restart; int /*<<< orphan*/  hdl; scalar_t__ kthread; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  msp_reset (struct i2c_client*) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msp_remove(struct i2c_client *client)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));

	v4l2_device_unregister_subdev(&state->sd);
	/* shutdown control thread */
	if (state->kthread) {
		state->restart = 1;
		kthread_stop(state->kthread);
	}
	msp_reset(client);

	v4l2_ctrl_handler_free(&state->hdl);
	return 0;
}