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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adv7511_state {int /*<<< orphan*/  cec_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int cec_register_adapter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct adv7511_state* get_adv7511_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7511_registered(struct v4l2_subdev *sd)
{
	struct adv7511_state *state = get_adv7511_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int err;

	err = cec_register_adapter(state->cec_adap, &client->dev);
	if (err)
		cec_delete_adapter(state->cec_adap);
	return err;
}