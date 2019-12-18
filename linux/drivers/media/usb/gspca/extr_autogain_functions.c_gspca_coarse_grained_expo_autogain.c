#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gspca_dev {int exp_too_low_cnt; int exp_too_high_cnt; TYPE_1__* exposure; TYPE_1__* gain; TYPE_1__* autogain; } ;
typedef  int s32 ;
struct TYPE_3__ {int maximum; int minimum; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ v4l2_ctrl_g_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (TYPE_1__*,int) ; 

int gspca_coarse_grained_expo_autogain(
			struct gspca_dev *gspca_dev,
			int avg_lum,
			int desired_avg_lum,
			int deadzone)
{
	s32 gain_low, gain_high, gain, orig_gain, exposure, orig_exposure;
	int steps, retval = 0;

	if (v4l2_ctrl_g_ctrl(gspca_dev->autogain) == 0)
		return 0;

	orig_gain = gain = v4l2_ctrl_g_ctrl(gspca_dev->gain);
	orig_exposure = exposure = v4l2_ctrl_g_ctrl(gspca_dev->exposure);

	gain_low  = (s32)(gspca_dev->gain->maximum - gspca_dev->gain->minimum) /
		    5 * 2 + gspca_dev->gain->minimum;
	gain_high = (s32)(gspca_dev->gain->maximum - gspca_dev->gain->minimum) /
		    5 * 4 + gspca_dev->gain->minimum;

	/* If we are of a multiple of deadzone, do multiple steps to reach the
	   desired lumination fast (with the risc of a slight overshoot) */
	steps = (desired_avg_lum - avg_lum) / deadzone;

	gspca_dbg(gspca_dev, D_FRAM, "autogain: lum: %d, desired: %d, steps: %d\n",
		  avg_lum, desired_avg_lum, steps);

	if ((gain + steps) > gain_high &&
	    exposure < gspca_dev->exposure->maximum) {
		gain = gain_high;
		gspca_dev->exp_too_low_cnt++;
		gspca_dev->exp_too_high_cnt = 0;
	} else if ((gain + steps) < gain_low &&
		   exposure > gspca_dev->exposure->minimum) {
		gain = gain_low;
		gspca_dev->exp_too_high_cnt++;
		gspca_dev->exp_too_low_cnt = 0;
	} else {
		gain += steps;
		if (gain > gspca_dev->gain->maximum)
			gain = gspca_dev->gain->maximum;
		else if (gain < gspca_dev->gain->minimum)
			gain = gspca_dev->gain->minimum;
		gspca_dev->exp_too_high_cnt = 0;
		gspca_dev->exp_too_low_cnt = 0;
	}

	if (gspca_dev->exp_too_high_cnt > 3) {
		exposure--;
		gspca_dev->exp_too_high_cnt = 0;
	} else if (gspca_dev->exp_too_low_cnt > 3) {
		exposure++;
		gspca_dev->exp_too_low_cnt = 0;
	}

	if (gain != orig_gain) {
		v4l2_ctrl_s_ctrl(gspca_dev->gain, gain);
		retval = 1;
	}
	if (exposure != orig_exposure) {
		v4l2_ctrl_s_ctrl(gspca_dev->exposure, exposure);
		retval = 1;
	}

	if (retval)
		gspca_dbg(gspca_dev, D_FRAM, "autogain: changed gain: %d, expo: %d\n",
			  gain, exposure);
	return retval;
}