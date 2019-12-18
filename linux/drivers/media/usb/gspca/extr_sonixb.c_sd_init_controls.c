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
struct sd {int sensor; int exposure_knee; int /*<<< orphan*/  plfreq; int /*<<< orphan*/  bridge; void* brightness; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct gspca_dev {void* autogain; void* exposure; void* gain; TYPE_1__ vdev; struct v4l2_ctrl_handler ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_103 ; 
#define  SENSOR_HV7131D 135 
#define  SENSOR_OV6650 134 
#define  SENSOR_OV7630 133 
#define  SENSOR_PAS106 132 
#define  SENSOR_PAS202 131 
#define  SENSOR_TAS5110C 130 
#define  SENSOR_TAS5110D 129 
#define  SENSOR_TAS5130CXX 128 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY_60HZ ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY_DISABLED ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sd_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 5);

	if (sd->sensor == SENSOR_OV6650 || sd->sensor == SENSOR_OV7630 ||
	    sd->sensor == SENSOR_PAS106 || sd->sensor == SENSOR_PAS202)
		sd->brightness = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_BRIGHTNESS, 0, 255, 1, 127);

	/* Gain range is sensor dependent */
	switch (sd->sensor) {
	case SENSOR_OV6650:
	case SENSOR_PAS106:
	case SENSOR_PAS202:
		gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_GAIN, 0, 31, 1, 15);
		break;
	case SENSOR_OV7630:
		gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_GAIN, 0, 47, 1, 31);
		break;
	case SENSOR_HV7131D:
		gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_GAIN, 0, 63, 1, 31);
		break;
	case SENSOR_TAS5110C:
	case SENSOR_TAS5110D:
	case SENSOR_TAS5130CXX:
		gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_GAIN, 0, 255, 1, 127);
		break;
	default:
		if (sd->bridge == BRIDGE_103) {
			gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
						V4L2_CID_GAIN, 0, 127, 1, 63);
		} else {
			gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
						V4L2_CID_GAIN, 0, 15, 1, 7);
		}
	}

	/* Exposure range is sensor dependent, and not all have exposure */
	switch (sd->sensor) {
	case SENSOR_HV7131D:
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_EXPOSURE, 0, 8191, 1, 482);
		sd->exposure_knee = 964;
		break;
	case SENSOR_OV6650:
	case SENSOR_OV7630:
	case SENSOR_PAS106:
	case SENSOR_PAS202:
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_EXPOSURE, 0, 1023, 1, 66);
		sd->exposure_knee = 200;
		break;
	case SENSOR_TAS5110C:
	case SENSOR_TAS5110D:
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_EXPOSURE, 2, 15, 1, 2);
		break;
	}

	if (gspca_dev->exposure) {
		gspca_dev->autogain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
						V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	}

	if (sd->sensor == SENSOR_OV6650 || sd->sensor == SENSOR_OV7630)
		sd->plfreq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0,
			V4L2_CID_POWER_LINE_FREQUENCY_DISABLED);

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}

	if (gspca_dev->autogain)
		v4l2_ctrl_auto_cluster(3, &gspca_dev->autogain, 0, false);

	return 0;
}