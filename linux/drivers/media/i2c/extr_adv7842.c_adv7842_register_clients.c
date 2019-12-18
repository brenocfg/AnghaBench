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
struct adv7842_platform_data {int /*<<< orphan*/  i2c_vdp; int /*<<< orphan*/  i2c_cp; int /*<<< orphan*/  i2c_hdmi; int /*<<< orphan*/  i2c_edid; int /*<<< orphan*/  i2c_repeater; int /*<<< orphan*/  i2c_afe; int /*<<< orphan*/  i2c_sdp; int /*<<< orphan*/  i2c_sdp_io; int /*<<< orphan*/  i2c_infoframe; int /*<<< orphan*/  i2c_cec; int /*<<< orphan*/  i2c_avlink; } ;
struct adv7842_state {void* i2c_vdp; void* i2c_cp; void* i2c_hdmi; void* i2c_edid; void* i2c_repeater; void* i2c_afe; void* i2c_sdp; void* i2c_sdp_io; void* i2c_infoframe; void* i2c_cec; void* i2c_avlink; struct adv7842_platform_data pdata; } ;

/* Variables and functions */
 void* adv7842_dummy_client (struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7842_register_clients(struct v4l2_subdev *sd)
{
	struct adv7842_state *state = to_state(sd);
	struct adv7842_platform_data *pdata = &state->pdata;

	state->i2c_avlink = adv7842_dummy_client(sd, "avlink", pdata->i2c_avlink, 0xf3);
	state->i2c_cec = adv7842_dummy_client(sd, "cec", pdata->i2c_cec, 0xf4);
	state->i2c_infoframe = adv7842_dummy_client(sd, "infoframe", pdata->i2c_infoframe, 0xf5);
	state->i2c_sdp_io = adv7842_dummy_client(sd, "sdp_io", pdata->i2c_sdp_io, 0xf2);
	state->i2c_sdp = adv7842_dummy_client(sd, "sdp", pdata->i2c_sdp, 0xf1);
	state->i2c_afe = adv7842_dummy_client(sd, "afe", pdata->i2c_afe, 0xf8);
	state->i2c_repeater = adv7842_dummy_client(sd, "repeater", pdata->i2c_repeater, 0xf9);
	state->i2c_edid = adv7842_dummy_client(sd, "edid", pdata->i2c_edid, 0xfa);
	state->i2c_hdmi = adv7842_dummy_client(sd, "hdmi", pdata->i2c_hdmi, 0xfb);
	state->i2c_cp = adv7842_dummy_client(sd, "cp", pdata->i2c_cp, 0xfd);
	state->i2c_vdp = adv7842_dummy_client(sd, "vdp", pdata->i2c_vdp, 0xfe);

	if (!state->i2c_avlink ||
	    !state->i2c_cec ||
	    !state->i2c_infoframe ||
	    !state->i2c_sdp_io ||
	    !state->i2c_sdp ||
	    !state->i2c_afe ||
	    !state->i2c_repeater ||
	    !state->i2c_edid ||
	    !state->i2c_hdmi ||
	    !state->i2c_cp ||
	    !state->i2c_vdp)
		return -1;

	return 0;
}