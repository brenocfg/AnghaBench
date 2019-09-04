#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sd {int resetlevel; int /*<<< orphan*/  expo_change_state; scalar_t__ resetlevel_adjust_dir; scalar_t__ resetlevel_frame_count; scalar_t__ restart_stream; scalar_t__ pixels_read; scalar_t__ packet_read; } ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; int usb_err; TYPE_3__ pixfmt; int /*<<< orphan*/  dev; TYPE_2__ cam; } ;
struct TYPE_4__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPO_NO_CHANGE ; 
 int /*<<< orphan*/  HV7131_REG_ARLV ; 
 int /*<<< orphan*/  HV7131_REG_MODE_B ; 
 int /*<<< orphan*/  SE401_OPERATINGMODE ; 
 int SE401_QUANT_FACT ; 
 int /*<<< orphan*/  SE401_REQ_CAMERA_POWER ; 
 int /*<<< orphan*/  SE401_REQ_LED_CONTROL ; 
 int /*<<< orphan*/  SE401_REQ_SET_HEIGHT ; 
 int /*<<< orphan*/  SE401_REQ_SET_WIDTH ; 
 int /*<<< orphan*/  SE401_REQ_START_CONTINUOUS_CAPTURE ; 
 int /*<<< orphan*/  se401_set_feature (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  se401_write_req (struct gspca_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	int mult = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	int mode = 0;

	se401_write_req(gspca_dev, SE401_REQ_CAMERA_POWER, 1, 1);
	if (gspca_dev->usb_err) {
		/* Sometimes after being idle for a while the se401 won't
		   respond and needs a good kicking  */
		usb_reset_device(gspca_dev->dev);
		gspca_dev->usb_err = 0;
		se401_write_req(gspca_dev, SE401_REQ_CAMERA_POWER, 1, 0);
	}
	se401_write_req(gspca_dev, SE401_REQ_LED_CONTROL, 1, 0);

	se401_set_feature(gspca_dev, HV7131_REG_MODE_B, 0x05);

	/* set size + mode */
	se401_write_req(gspca_dev, SE401_REQ_SET_WIDTH,
			gspca_dev->pixfmt.width * mult, 0);
	se401_write_req(gspca_dev, SE401_REQ_SET_HEIGHT,
			gspca_dev->pixfmt.height * mult, 0);
	/*
	 * HDG: disabled this as it does not seem to do anything
	 * se401_write_req(gspca_dev, SE401_REQ_SET_OUTPUT_MODE,
	 *		   SE401_FORMAT_BAYER, 0);
	 */

	switch (mult) {
	case 1: /* Raw bayer */
		mode = 0x03; break;
	case 2: /* 1/4th janggu */
		mode = SE401_QUANT_FACT << 4; break;
	case 4: /* 1/16th janggu */
		mode = (SE401_QUANT_FACT << 4) | 0x02; break;
	}
	se401_set_feature(gspca_dev, SE401_OPERATINGMODE, mode);

	se401_set_feature(gspca_dev, HV7131_REG_ARLV, sd->resetlevel);

	sd->packet_read = 0;
	sd->pixels_read = 0;
	sd->restart_stream = 0;
	sd->resetlevel_frame_count = 0;
	sd->resetlevel_adjust_dir = 0;
	sd->expo_change_state = EXPO_NO_CHANGE;

	se401_write_req(gspca_dev, SE401_REQ_START_CONTINUOUS_CAPTURE, 0, 0);

	return gspca_dev->usb_err;
}