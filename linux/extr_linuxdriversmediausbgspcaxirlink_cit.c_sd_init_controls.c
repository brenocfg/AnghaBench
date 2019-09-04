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
struct v4l2_ctrl_handler {int error; } ;
struct sd {int model; int /*<<< orphan*/  lighting; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct gspca_dev {TYPE_1__ vdev; struct v4l2_ctrl_handler ctrl_handler; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  V4L2_CID_BACKLIGHT_COMPENSATION ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SHARPNESS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sd_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	bool has_brightness;
	bool has_contrast;
	bool has_hue;
	bool has_sharpness;
	bool has_lighting;
	bool has_hflip;

	has_brightness = has_contrast = has_hue =
		has_sharpness = has_hflip = has_lighting = false;
	switch (sd->model) {
	case CIT_MODEL0:
		has_contrast = has_hflip = true;
		break;
	case CIT_MODEL1:
		has_brightness = has_contrast =
			has_sharpness = has_lighting = true;
		break;
	case CIT_MODEL2:
		has_brightness = has_hue = has_lighting = true;
		break;
	case CIT_MODEL3:
		has_brightness = has_contrast = has_sharpness = true;
		break;
	case CIT_MODEL4:
		has_brightness = has_hue = true;
		break;
	case CIT_IBM_NETCAM_PRO:
		has_brightness = has_hue =
			has_sharpness = has_hflip = has_lighting = true;
		break;
	}
	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 5);
	if (has_brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 63, 1, 32);
	if (has_contrast)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 20, 1, 10);
	if (has_hue)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 0, 127, 1, 63);
	if (has_sharpness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 6, 1, 3);
	if (has_lighting)
		sd->lighting = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BACKLIGHT_COMPENSATION, 0, 2, 1, 1);
	if (has_hflip)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}
	return 0;
}