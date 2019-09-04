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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct ad9389b_state_edid {int /*<<< orphan*/  blocks; scalar_t__ segments; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ad9389b_state {TYPE_1__ dv_timings; int /*<<< orphan*/  edid_detect_counter; scalar_t__ power_on; int /*<<< orphan*/  chip_revision; struct ad9389b_state_edid edid; } ;

/* Variables and functions */
 int MASK_AD9389B_HPD_DETECT ; 
 int MASK_AD9389B_MSEN_DETECT ; 
 scalar_t__ V4L2_DV_BT_656_1120 ; 
 int ad9389b_rd (struct v4l2_subdev*,int) ; 
 struct ad9389b_state* get_ad9389b_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 
 int /*<<< orphan*/  v4l2_print_dv_timings (int /*<<< orphan*/ ,char*,TYPE_1__*,int) ; 

__attribute__((used)) static int ad9389b_log_status(struct v4l2_subdev *sd)
{
	struct ad9389b_state *state = get_ad9389b_state(sd);
	struct ad9389b_state_edid *edid = &state->edid;

	static const char * const states[] = {
		"in reset",
		"reading EDID",
		"idle",
		"initializing HDCP",
		"HDCP enabled",
		"initializing HDCP repeater",
		"6", "7", "8", "9", "A", "B", "C", "D", "E", "F"
	};
	static const char * const errors[] = {
		"no error",
		"bad receiver BKSV",
		"Ri mismatch",
		"Pj mismatch",
		"i2c error",
		"timed out",
		"max repeater cascade exceeded",
		"hash check failed",
		"too many devices",
		"9", "A", "B", "C", "D", "E", "F"
	};

	u8 manual_gear;

	v4l2_info(sd, "chip revision %d\n", state->chip_revision);
	v4l2_info(sd, "power %s\n", state->power_on ? "on" : "off");
	v4l2_info(sd, "%s hotplug, %s Rx Sense, %s EDID (%d block(s))\n",
		  (ad9389b_rd(sd, 0x42) & MASK_AD9389B_HPD_DETECT) ?
		  "detected" : "no",
		  (ad9389b_rd(sd, 0x42) & MASK_AD9389B_MSEN_DETECT) ?
		  "detected" : "no",
		  edid->segments ? "found" : "no", edid->blocks);
	v4l2_info(sd, "%s output %s\n",
		  (ad9389b_rd(sd, 0xaf) & 0x02) ?
		  "HDMI" : "DVI-D",
		  (ad9389b_rd(sd, 0xa1) & 0x3c) ?
		  "disabled" : "enabled");
	v4l2_info(sd, "ad9389b: %s\n", (ad9389b_rd(sd, 0xb8) & 0x40) ?
		  "encrypted" : "no encryption");
	v4l2_info(sd, "state: %s, error: %s, detect count: %u, msk/irq: %02x/%02x\n",
		  states[ad9389b_rd(sd, 0xc8) & 0xf],
		  errors[ad9389b_rd(sd, 0xc8) >> 4],
		  state->edid_detect_counter,
		  ad9389b_rd(sd, 0x94), ad9389b_rd(sd, 0x96));
	manual_gear = ad9389b_rd(sd, 0x98) & 0x80;
	v4l2_info(sd, "ad9389b: RGB quantization: %s range\n",
		  ad9389b_rd(sd, 0x3b) & 0x01 ? "limited" : "full");
	v4l2_info(sd, "ad9389b: %s gear %d\n",
		  manual_gear ? "manual" : "automatic",
		  manual_gear ? ((ad9389b_rd(sd, 0x98) & 0x70) >> 4) :
		  ((ad9389b_rd(sd, 0x9e) & 0x0e) >> 1));
	if (ad9389b_rd(sd, 0xaf) & 0x02) {
		/* HDMI only */
		u8 manual_cts = ad9389b_rd(sd, 0x0a) & 0x80;
		u32 N = (ad9389b_rd(sd, 0x01) & 0xf) << 16 |
			ad9389b_rd(sd, 0x02) << 8 |
			ad9389b_rd(sd, 0x03);
		u8 vic_detect = ad9389b_rd(sd, 0x3e) >> 2;
		u8 vic_sent = ad9389b_rd(sd, 0x3d) & 0x3f;
		u32 CTS;

		if (manual_cts)
			CTS = (ad9389b_rd(sd, 0x07) & 0xf) << 16 |
			      ad9389b_rd(sd, 0x08) << 8 |
			      ad9389b_rd(sd, 0x09);
		else
			CTS = (ad9389b_rd(sd, 0x04) & 0xf) << 16 |
			      ad9389b_rd(sd, 0x05) << 8 |
			      ad9389b_rd(sd, 0x06);
		N = (ad9389b_rd(sd, 0x01) & 0xf) << 16 |
		    ad9389b_rd(sd, 0x02) << 8 |
		    ad9389b_rd(sd, 0x03);

		v4l2_info(sd, "ad9389b: CTS %s mode: N %d, CTS %d\n",
			  manual_cts ? "manual" : "automatic", N, CTS);

		v4l2_info(sd, "ad9389b: VIC: detected %d, sent %d\n",
			  vic_detect, vic_sent);
	}
	if (state->dv_timings.type == V4L2_DV_BT_656_1120)
		v4l2_print_dv_timings(sd->name, "timings: ",
				&state->dv_timings, false);
	else
		v4l2_info(sd, "no timings set\n");
	return 0;
}