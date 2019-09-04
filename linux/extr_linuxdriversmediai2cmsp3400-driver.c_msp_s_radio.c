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
struct msp_state {int radio; int opmode; scalar_t__ watch_stereo; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_CARRIER (double) ; 
 int /*<<< orphan*/  MSP_MODE_FM_RADIO ; 
#define  OPMODE_AUTODETECT 130 
#define  OPMODE_AUTOSELECT 129 
#define  OPMODE_MANUAL 128 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msp3400c_set_carrier (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp3400c_set_mode (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_update_volume (struct msp_state*) ; 
 int /*<<< orphan*/  msp_wake_thread (struct i2c_client*) ; 
 struct msp_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int msp_s_radio(struct v4l2_subdev *sd)
{
	struct msp_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (state->radio)
		return 0;
	state->radio = 1;
	dev_dbg_lvl(&client->dev, 1, msp_debug, "switching to radio mode\n");
	state->watch_stereo = 0;
	switch (state->opmode) {
	case OPMODE_MANUAL:
		/* set msp3400 to FM radio mode */
		msp3400c_set_mode(client, MSP_MODE_FM_RADIO);
		msp3400c_set_carrier(client, MSP_CARRIER(10.7),
				MSP_CARRIER(10.7));
		msp_update_volume(state);
		break;
	case OPMODE_AUTODETECT:
	case OPMODE_AUTOSELECT:
		/* the thread will do for us */
		msp_wake_thread(client);
		break;
	}
	return 0;
}