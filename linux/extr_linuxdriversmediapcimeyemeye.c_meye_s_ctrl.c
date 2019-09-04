#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int id; int val; } ;
struct TYPE_3__ {int agc; int sharpness; int picture; int quality; int framerate; } ;
struct TYPE_4__ {int brightness; int hue; int contrast; int colour; int /*<<< orphan*/  lock; TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAAGC ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERABRIGHTNESS ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERACOLOR ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERACONTRAST ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAHUE ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAPICTURE ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERASHARPNESS ; 
#define  V4L2_CID_BRIGHTNESS 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_HUE 134 
#define  V4L2_CID_JPEG_COMPRESSION_QUALITY 133 
#define  V4L2_CID_MEYE_AGC 132 
#define  V4L2_CID_MEYE_FRAMERATE 131 
#define  V4L2_CID_MEYE_PICTURE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 TYPE_2__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sony_pic_camera_command (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meye_s_ctrl(struct v4l2_ctrl *ctrl)
{
	mutex_lock(&meye.lock);
	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERABRIGHTNESS, ctrl->val);
		meye.brightness = ctrl->val << 10;
		break;
	case V4L2_CID_HUE:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAHUE, ctrl->val);
		meye.hue = ctrl->val << 10;
		break;
	case V4L2_CID_CONTRAST:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERACONTRAST, ctrl->val);
		meye.contrast = ctrl->val << 10;
		break;
	case V4L2_CID_SATURATION:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERACOLOR, ctrl->val);
		meye.colour = ctrl->val << 10;
		break;
	case V4L2_CID_MEYE_AGC:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAAGC, ctrl->val);
		meye.params.agc = ctrl->val;
		break;
	case V4L2_CID_SHARPNESS:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERASHARPNESS, ctrl->val);
		meye.params.sharpness = ctrl->val;
		break;
	case V4L2_CID_MEYE_PICTURE:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAPICTURE, ctrl->val);
		meye.params.picture = ctrl->val;
		break;
	case V4L2_CID_JPEG_COMPRESSION_QUALITY:
		meye.params.quality = ctrl->val;
		break;
	case V4L2_CID_MEYE_FRAMERATE:
		meye.params.framerate = ctrl->val;
		break;
	default:
		mutex_unlock(&meye.lock);
		return -EINVAL;
	}
	mutex_unlock(&meye.lock);

	return 0;
}