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
struct v4l2_ctrl {int id; } ;

/* Variables and functions */
#define  V4L2_CID_AUDIO_MUTE 135 
#define  V4L2_CID_AUDIO_VOLUME 134 
#define  V4L2_CID_BRIGHTNESS 133 
#define  V4L2_CID_CONTRAST 132 
#define  V4L2_CID_HUE 131 
#define  V4L2_CID_PRIVATE_AUTOMUTE 130 
#define  V4L2_CID_PRIVATE_INVERT 129 
#define  V4L2_CID_SATURATION 128 

__attribute__((used)) static bool empress_ctrl_filter(const struct v4l2_ctrl *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
	case V4L2_CID_HUE:
	case V4L2_CID_CONTRAST:
	case V4L2_CID_SATURATION:
	case V4L2_CID_AUDIO_MUTE:
	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_PRIVATE_INVERT:
	case V4L2_CID_PRIVATE_AUTOMUTE:
		return true;
	default:
		return false;
	}
}