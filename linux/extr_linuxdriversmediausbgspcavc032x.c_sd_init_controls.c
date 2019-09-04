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
struct sd {int sensor; void* hflip; void* vflip; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct gspca_dev {TYPE_1__ vdev; struct v4l2_ctrl_handler ctrl_handler; } ;

/* Variables and functions */
#define  SENSOR_HV7131R 137 
#define  SENSOR_MI0360 136 
#define  SENSOR_MI1310_SOC 135 
#define  SENSOR_MI1320 134 
#define  SENSOR_MI1320_SOC 133 
#define  SENSOR_OV7660 132 
#define  SENSOR_OV7670 131 
#define  SENSOR_PO1200 130 
#define  SENSOR_PO3130NC 129 
#define  SENSOR_POxxxx 128 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_BACKLIGHT_COMPENSATION ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY_50HZ ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY_60HZ ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_SHARPNESS ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sd_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	bool has_brightness = false;
	bool has_contrast = false;
	bool has_sat = false;
	bool has_hvflip = false;
	bool has_freq = false;
	bool has_backlight = false;
	bool has_exposure = false;
	bool has_autogain = false;
	bool has_gain = false;
	bool has_sharpness = false;

	switch (sd->sensor) {
	case SENSOR_HV7131R:
	case SENSOR_MI0360:
	case SENSOR_PO3130NC:
		break;
	case SENSOR_MI1310_SOC:
	case SENSOR_MI1320:
	case SENSOR_MI1320_SOC:
	case SENSOR_OV7660:
		has_hvflip = true;
		break;
	case SENSOR_OV7670:
		has_hvflip = has_freq = true;
		break;
	case SENSOR_PO1200:
		has_hvflip = has_sharpness = true;
		break;
	case SENSOR_POxxxx:
		has_brightness = has_contrast = has_sat = has_backlight =
			has_exposure = has_autogain = has_gain =
			has_sharpness = true;
		break;
	}

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 8);
	if (has_brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	if (has_contrast)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 127);
	if (has_sat)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 1, 127, 1, 63);
	if (has_hvflip) {
		sd->hflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
		sd->vflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	}
	if (has_sharpness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, -1, 2, 1, -1);
	if (has_freq)
		v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0,
			V4L2_CID_POWER_LINE_FREQUENCY_50HZ);
	if (has_autogain)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	if (has_gain)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 78, 1, 0);
	if (has_exposure)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 4095, 1, 450);
	if (has_backlight)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BACKLIGHT_COMPENSATION, 0, 15, 1, 15);

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}
	if (sd->hflip)
		v4l2_ctrl_cluster(2, &sd->hflip);
	return 0;
}