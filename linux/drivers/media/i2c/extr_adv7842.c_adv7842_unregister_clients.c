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
struct adv7842_state {int /*<<< orphan*/ * i2c_vdp; int /*<<< orphan*/ * i2c_cp; int /*<<< orphan*/ * i2c_hdmi; int /*<<< orphan*/ * i2c_edid; int /*<<< orphan*/ * i2c_repeater; int /*<<< orphan*/ * i2c_afe; int /*<<< orphan*/ * i2c_sdp; int /*<<< orphan*/ * i2c_sdp_io; int /*<<< orphan*/ * i2c_infoframe; int /*<<< orphan*/ * i2c_cec; int /*<<< orphan*/ * i2c_avlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void adv7842_unregister_clients(struct v4l2_subdev *sd)
{
	struct adv7842_state *state = to_state(sd);
	i2c_unregister_device(state->i2c_avlink);
	i2c_unregister_device(state->i2c_cec);
	i2c_unregister_device(state->i2c_infoframe);
	i2c_unregister_device(state->i2c_sdp_io);
	i2c_unregister_device(state->i2c_sdp);
	i2c_unregister_device(state->i2c_afe);
	i2c_unregister_device(state->i2c_repeater);
	i2c_unregister_device(state->i2c_edid);
	i2c_unregister_device(state->i2c_hdmi);
	i2c_unregister_device(state->i2c_cp);
	i2c_unregister_device(state->i2c_vdp);

	state->i2c_avlink = NULL;
	state->i2c_cec = NULL;
	state->i2c_infoframe = NULL;
	state->i2c_sdp_io = NULL;
	state->i2c_sdp = NULL;
	state->i2c_afe = NULL;
	state->i2c_repeater = NULL;
	state->i2c_edid = NULL;
	state->i2c_hdmi = NULL;
	state->i2c_cp = NULL;
	state->i2c_vdp = NULL;
}