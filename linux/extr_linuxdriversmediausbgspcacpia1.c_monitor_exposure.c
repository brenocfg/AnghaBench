#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int coarseExpHi; int coarseExpLo; scalar_t__ gain; int gainMode; } ;
struct TYPE_8__ {int divisor; size_t baserate; } ;
struct TYPE_7__ {int coarseJump; int /*<<< orphan*/  disabled; } ;
struct TYPE_6__ {int brightness; } ;
struct TYPE_10__ {TYPE_4__ exposure; TYPE_3__ sensorFps; TYPE_2__ flickerControl; TYPE_1__ colourParams; } ;
struct sd {scalar_t__ exposure_status; int exposure_count; size_t mainsFreq; TYPE_5__ params; int /*<<< orphan*/  fps; } ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int CPIA_COMMAND_ReadVPRegs ; 
 int DARK_TIME ; 
 int /*<<< orphan*/  D_CONF ; 
 scalar_t__ EXPOSURE_DARK ; 
 scalar_t__ EXPOSURE_LIGHT ; 
 void* EXPOSURE_NORMAL ; 
 scalar_t__ EXPOSURE_VERY_DARK ; 
 scalar_t__ EXPOSURE_VERY_LIGHT ; 
 int EXP_ACC_DARK ; 
 int EXP_ACC_LIGHT ; 
 scalar_t__ FIRMWARE_VERSION (int,int) ; 
 int HIGH_COMP_102 ; 
 int LIGHT_TIME ; 
 int LOW_EXP ; 
 int MAX_COMP ; 
 int MAX_EXP ; 
 int MAX_EXP_102 ; 
 int TC ; 
 int VERY_LOW_EXP ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_setexposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  command_setflickerctrl (struct gspca_dev*) ; 
 int /*<<< orphan*/  command_setsensorfps (struct gspca_dev*) ; 
 int cpia_usb_transferCmd (struct gspca_dev*,int*) ; 
 void**** flicker_jumps ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void monitor_exposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 exp_acc, bcomp, cmd[8];
	int ret, light_exp, dark_exp, very_dark_exp;
	int old_exposure, new_exposure, framerate;
	int setfps = 0, setexp = 0, setflicker = 0;

	/* get necessary stats and register settings from camera */
	/* do_command can't handle this, so do it ourselves */
	cmd[0] = CPIA_COMMAND_ReadVPRegs >> 8;
	cmd[1] = CPIA_COMMAND_ReadVPRegs & 0xff;
	cmd[2] = 30;
	cmd[3] = 4;
	cmd[4] = 9;
	cmd[5] = 8;
	cmd[6] = 8;
	cmd[7] = 0;
	ret = cpia_usb_transferCmd(gspca_dev, cmd);
	if (ret) {
		pr_err("ReadVPRegs(30,4,9,8) - failed: %d\n", ret);
		return;
	}
	exp_acc = gspca_dev->usb_buf[0];
	bcomp = gspca_dev->usb_buf[1];

	light_exp = sd->params.colourParams.brightness +
		    TC - 50 + EXP_ACC_LIGHT;
	if (light_exp > 255)
		light_exp = 255;
	dark_exp = sd->params.colourParams.brightness +
		   TC - 50 - EXP_ACC_DARK;
	if (dark_exp < 0)
		dark_exp = 0;
	very_dark_exp = dark_exp / 2;

	old_exposure = sd->params.exposure.coarseExpHi * 256 +
		       sd->params.exposure.coarseExpLo;

	if (!sd->params.flickerControl.disabled) {
		/* Flicker control on */
		int max_comp = FIRMWARE_VERSION(1, 2) ? MAX_COMP :
							HIGH_COMP_102;
		bcomp += 128;	/* decode */
		if (bcomp >= max_comp && exp_acc < dark_exp) {
			/* dark */
			if (exp_acc < very_dark_exp) {
				/* very dark */
				if (sd->exposure_status == EXPOSURE_VERY_DARK)
					++sd->exposure_count;
				else {
					sd->exposure_status =
						EXPOSURE_VERY_DARK;
					sd->exposure_count = 1;
				}
			} else {
				/* just dark */
				if (sd->exposure_status == EXPOSURE_DARK)
					++sd->exposure_count;
				else {
					sd->exposure_status = EXPOSURE_DARK;
					sd->exposure_count = 1;
				}
			}
		} else if (old_exposure <= LOW_EXP || exp_acc > light_exp) {
			/* light */
			if (old_exposure <= VERY_LOW_EXP) {
				/* very light */
				if (sd->exposure_status == EXPOSURE_VERY_LIGHT)
					++sd->exposure_count;
				else {
					sd->exposure_status =
						EXPOSURE_VERY_LIGHT;
					sd->exposure_count = 1;
				}
			} else {
				/* just light */
				if (sd->exposure_status == EXPOSURE_LIGHT)
					++sd->exposure_count;
				else {
					sd->exposure_status = EXPOSURE_LIGHT;
					sd->exposure_count = 1;
				}
			}
		} else {
			/* not dark or light */
			sd->exposure_status = EXPOSURE_NORMAL;
		}
	} else {
		/* Flicker control off */
		if (old_exposure >= MAX_EXP && exp_acc < dark_exp) {
			/* dark */
			if (exp_acc < very_dark_exp) {
				/* very dark */
				if (sd->exposure_status == EXPOSURE_VERY_DARK)
					++sd->exposure_count;
				else {
					sd->exposure_status =
						EXPOSURE_VERY_DARK;
					sd->exposure_count = 1;
				}
			} else {
				/* just dark */
				if (sd->exposure_status == EXPOSURE_DARK)
					++sd->exposure_count;
				else {
					sd->exposure_status = EXPOSURE_DARK;
					sd->exposure_count = 1;
				}
			}
		} else if (old_exposure <= LOW_EXP || exp_acc > light_exp) {
			/* light */
			if (old_exposure <= VERY_LOW_EXP) {
				/* very light */
				if (sd->exposure_status == EXPOSURE_VERY_LIGHT)
					++sd->exposure_count;
				else {
					sd->exposure_status =
						EXPOSURE_VERY_LIGHT;
					sd->exposure_count = 1;
				}
			} else {
				/* just light */
				if (sd->exposure_status == EXPOSURE_LIGHT)
					++sd->exposure_count;
				else {
					sd->exposure_status = EXPOSURE_LIGHT;
					sd->exposure_count = 1;
				}
			}
		} else {
			/* not dark or light */
			sd->exposure_status = EXPOSURE_NORMAL;
		}
	}

	framerate = atomic_read(&sd->fps);
	if (framerate > 30 || framerate < 1)
		framerate = 1;

	if (!sd->params.flickerControl.disabled) {
		/* Flicker control on */
		if ((sd->exposure_status == EXPOSURE_VERY_DARK ||
		     sd->exposure_status == EXPOSURE_DARK) &&
		    sd->exposure_count >= DARK_TIME * framerate &&
		    sd->params.sensorFps.divisor < 2) {

			/* dark for too long */
			++sd->params.sensorFps.divisor;
			setfps = 1;

			sd->params.flickerControl.coarseJump =
				flicker_jumps[sd->mainsFreq]
					     [sd->params.sensorFps.baserate]
					     [sd->params.sensorFps.divisor];
			setflicker = 1;

			new_exposure = sd->params.flickerControl.coarseJump-1;
			while (new_exposure < old_exposure / 2)
				new_exposure +=
					sd->params.flickerControl.coarseJump;
			sd->params.exposure.coarseExpLo = new_exposure & 0xff;
			sd->params.exposure.coarseExpHi = new_exposure >> 8;
			setexp = 1;
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically decreasing sensor_fps\n");

		} else if ((sd->exposure_status == EXPOSURE_VERY_LIGHT ||
			    sd->exposure_status == EXPOSURE_LIGHT) &&
			   sd->exposure_count >= LIGHT_TIME * framerate &&
			   sd->params.sensorFps.divisor > 0) {

			/* light for too long */
			int max_exp = FIRMWARE_VERSION(1, 2) ? MAX_EXP_102 :
							       MAX_EXP;
			--sd->params.sensorFps.divisor;
			setfps = 1;

			sd->params.flickerControl.coarseJump =
				flicker_jumps[sd->mainsFreq]
					     [sd->params.sensorFps.baserate]
					     [sd->params.sensorFps.divisor];
			setflicker = 1;

			new_exposure = sd->params.flickerControl.coarseJump-1;
			while (new_exposure < 2 * old_exposure &&
			       new_exposure +
			       sd->params.flickerControl.coarseJump < max_exp)
				new_exposure +=
					sd->params.flickerControl.coarseJump;
			sd->params.exposure.coarseExpLo = new_exposure & 0xff;
			sd->params.exposure.coarseExpHi = new_exposure >> 8;
			setexp = 1;
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically increasing sensor_fps\n");
		}
	} else {
		/* Flicker control off */
		if ((sd->exposure_status == EXPOSURE_VERY_DARK ||
		     sd->exposure_status == EXPOSURE_DARK) &&
		    sd->exposure_count >= DARK_TIME * framerate &&
		    sd->params.sensorFps.divisor < 2) {

			/* dark for too long */
			++sd->params.sensorFps.divisor;
			setfps = 1;

			if (sd->params.exposure.gain > 0) {
				--sd->params.exposure.gain;
				setexp = 1;
			}
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically decreasing sensor_fps\n");

		} else if ((sd->exposure_status == EXPOSURE_VERY_LIGHT ||
			    sd->exposure_status == EXPOSURE_LIGHT) &&
			   sd->exposure_count >= LIGHT_TIME * framerate &&
			   sd->params.sensorFps.divisor > 0) {

			/* light for too long */
			--sd->params.sensorFps.divisor;
			setfps = 1;

			if (sd->params.exposure.gain <
			    sd->params.exposure.gainMode - 1) {
				++sd->params.exposure.gain;
				setexp = 1;
			}
			sd->exposure_status = EXPOSURE_NORMAL;
			gspca_dbg(gspca_dev, D_CONF, "Automatically increasing sensor_fps\n");
		}
	}

	if (setexp)
		command_setexposure(gspca_dev);

	if (setfps)
		command_setsensorfps(gspca_dev);

	if (setflicker)
		command_setflickerctrl(gspca_dev);
}