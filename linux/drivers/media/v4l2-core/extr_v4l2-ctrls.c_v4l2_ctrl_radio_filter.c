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
#define  V4L2_CID_AUDIO_BALANCE 133 
#define  V4L2_CID_AUDIO_BASS 132 
#define  V4L2_CID_AUDIO_LOUDNESS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 scalar_t__ V4L2_CTRL_CLASS_FM_RX ; 
 scalar_t__ V4L2_CTRL_CLASS_FM_TX ; 
 scalar_t__ V4L2_CTRL_ID2WHICH (int) ; 

bool v4l2_ctrl_radio_filter(const struct v4l2_ctrl *ctrl)
{
	if (V4L2_CTRL_ID2WHICH(ctrl->id) == V4L2_CTRL_CLASS_FM_TX)
		return true;
	if (V4L2_CTRL_ID2WHICH(ctrl->id) == V4L2_CTRL_CLASS_FM_RX)
		return true;
	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_AUDIO_BALANCE:
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
	case V4L2_CID_AUDIO_LOUDNESS:
		return true;
	default:
		break;
	}
	return false;
}