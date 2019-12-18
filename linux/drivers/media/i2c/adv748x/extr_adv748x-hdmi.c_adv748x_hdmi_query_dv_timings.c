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
struct v4l2_bt_timings {int pixelclock; scalar_t__ interlaced; int width; int height; int hfrontporch; int hsync; int hbackporch; int vfrontporch; int vsync; int vbackporch; int polarities; int il_vfrontporch; int il_vsync; int il_vbackporch; } ;
struct v4l2_dv_timings {int /*<<< orphan*/  type; struct v4l2_bt_timings bt; } ;
struct adv748x_state {int dummy; } ;
struct adv748x_hdmi {struct v4l2_dv_timings timings; } ;

/* Variables and functions */
 int ADV748X_HDMI_F0H1 ; 
 int ADV748X_HDMI_F0H1_HEIGHT_MASK ; 
 int ADV748X_HDMI_F1H1 ; 
 int ADV748X_HDMI_F1H1_INTERLACED ; 
 int ADV748X_HDMI_HBACK_PORCH ; 
 int ADV748X_HDMI_HBACK_PORCH_MASK ; 
 int ADV748X_HDMI_HFRONT_PORCH ; 
 int ADV748X_HDMI_HFRONT_PORCH_MASK ; 
 int ADV748X_HDMI_HSYNC_WIDTH ; 
 int ADV748X_HDMI_HSYNC_WIDTH_MASK ; 
 int ADV748X_HDMI_LW1 ; 
 int ADV748X_HDMI_LW1_WIDTH_MASK ; 
 int ADV748X_HDMI_VBACK_PORCH ; 
 int ADV748X_HDMI_VBACK_PORCH_MASK ; 
 int ADV748X_HDMI_VFRONT_PORCH ; 
 int ADV748X_HDMI_VFRONT_PORCH_MASK ; 
 int ADV748X_HDMI_VSYNC_WIDTH ; 
 int ADV748X_HDMI_VSYNC_WIDTH_MASK ; 
 int BIT (int) ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOLINK ; 
 int /*<<< orphan*/  V4L2_DV_BT_656_1120 ; 
 int V4L2_DV_HSYNC_POS_POL ; 
 scalar_t__ V4L2_DV_INTERLACED ; 
 scalar_t__ V4L2_DV_PROGRESSIVE ; 
 int V4L2_DV_VSYNC_POS_POL ; 
 int /*<<< orphan*/  adv748x_fill_optional_dv_timings (struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  adv748x_hdmi_has_signal (struct adv748x_state*) ; 
 int adv748x_hdmi_read_pixelclock (struct adv748x_state*) ; 
 struct adv748x_state* adv748x_hdmi_to_state (struct adv748x_hdmi*) ; 
 struct adv748x_hdmi* adv748x_sd_to_hdmi (struct v4l2_subdev*) ; 
 int hdmi_read (struct adv748x_state*,int) ; 
 int hdmi_read16 (struct adv748x_state*,int,int) ; 
 int /*<<< orphan*/  memset (struct v4l2_dv_timings*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adv748x_hdmi_query_dv_timings(struct v4l2_subdev *sd,
					 struct v4l2_dv_timings *timings)
{
	struct adv748x_hdmi *hdmi = adv748x_sd_to_hdmi(sd);
	struct adv748x_state *state = adv748x_hdmi_to_state(hdmi);
	struct v4l2_bt_timings *bt = &timings->bt;
	int pixelclock;
	int polarity;

	if (!timings)
		return -EINVAL;

	memset(timings, 0, sizeof(struct v4l2_dv_timings));

	if (!adv748x_hdmi_has_signal(state))
		return -ENOLINK;

	pixelclock = adv748x_hdmi_read_pixelclock(state);
	if (pixelclock < 0)
		return -ENODATA;

	timings->type = V4L2_DV_BT_656_1120;

	bt->pixelclock = pixelclock;
	bt->interlaced = hdmi_read(state, ADV748X_HDMI_F1H1) &
				ADV748X_HDMI_F1H1_INTERLACED ?
				V4L2_DV_INTERLACED : V4L2_DV_PROGRESSIVE;
	bt->width = hdmi_read16(state, ADV748X_HDMI_LW1,
				ADV748X_HDMI_LW1_WIDTH_MASK);
	bt->height = hdmi_read16(state, ADV748X_HDMI_F0H1,
				 ADV748X_HDMI_F0H1_HEIGHT_MASK);
	bt->hfrontporch = hdmi_read16(state, ADV748X_HDMI_HFRONT_PORCH,
				      ADV748X_HDMI_HFRONT_PORCH_MASK);
	bt->hsync = hdmi_read16(state, ADV748X_HDMI_HSYNC_WIDTH,
				ADV748X_HDMI_HSYNC_WIDTH_MASK);
	bt->hbackporch = hdmi_read16(state, ADV748X_HDMI_HBACK_PORCH,
				     ADV748X_HDMI_HBACK_PORCH_MASK);
	bt->vfrontporch = hdmi_read16(state, ADV748X_HDMI_VFRONT_PORCH,
				      ADV748X_HDMI_VFRONT_PORCH_MASK) / 2;
	bt->vsync = hdmi_read16(state, ADV748X_HDMI_VSYNC_WIDTH,
				ADV748X_HDMI_VSYNC_WIDTH_MASK) / 2;
	bt->vbackporch = hdmi_read16(state, ADV748X_HDMI_VBACK_PORCH,
				     ADV748X_HDMI_VBACK_PORCH_MASK) / 2;

	polarity = hdmi_read(state, 0x05);
	bt->polarities = (polarity & BIT(4) ? V4L2_DV_VSYNC_POS_POL : 0) |
		(polarity & BIT(5) ? V4L2_DV_HSYNC_POS_POL : 0);

	if (bt->interlaced == V4L2_DV_INTERLACED) {
		bt->height += hdmi_read16(state, 0x0b, 0x1fff);
		bt->il_vfrontporch = hdmi_read16(state, 0x2c, 0x3fff) / 2;
		bt->il_vsync = hdmi_read16(state, 0x30, 0x3fff) / 2;
		bt->il_vbackporch = hdmi_read16(state, 0x34, 0x3fff) / 2;
	}

	adv748x_fill_optional_dv_timings(timings);

	/*
	 * No interrupt handling is implemented yet.
	 * There should be an IRQ when a cable is plugged and the new timings
	 * should be figured out and stored to state.
	 */
	hdmi->timings = *timings;

	return 0;
}