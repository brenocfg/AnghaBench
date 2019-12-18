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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tuner_analog_msg_data ;
typedef  int /*<<< orphan*/  subfmt ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_3__ format; int /*<<< orphan*/  which; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_usb_device {TYPE_2__* udev; int /*<<< orphan*/  i2c_adap; struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int input; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  cx25840; int /*<<< orphan*/  norm; int /*<<< orphan*/  tuner; int /*<<< orphan*/  tda9887; TYPE_1__* videodev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ARRAY_SIZE (struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  CX25840_COMPOSITE1 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  core ; 
 struct v4l2_subdev_format* cxusub_medion_pin_config ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  s_io_pin_config ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  set_fmt ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  video ; 

int cxusb_medion_analog_init(struct dvb_usb_device *dvbdev)
{
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	u8 tuner_analog_msg_data[] = { 0x9c, 0x60, 0x85, 0x54 };
	struct i2c_msg tuner_analog_msg = { .addr = 0x61, .flags = 0,
					    .buf = tuner_analog_msg_data,
					    .len =
					    sizeof(tuner_analog_msg_data) };
	struct v4l2_subdev_format subfmt;
	int ret;

	/* switch tuner to analog mode so IF demod will become accessible */
	ret = i2c_transfer(&dvbdev->i2c_adap, &tuner_analog_msg, 1);
	if (ret != 1)
		dev_warn(&dvbdev->udev->dev,
			 "tuner analog switch failed (%d)\n", ret);

	/*
	 * cx25840 might have lost power during mode switching so we need
	 * to set it again
	 */
	ret = v4l2_subdev_call(cxdev->cx25840, core, reset, 0);
	if (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 reset failed (%d)\n", ret);

	ret = v4l2_subdev_call(cxdev->cx25840, video, s_routing,
			       CX25840_COMPOSITE1, 0, 0);
	if (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 initial input setting failed (%d)\n", ret);

	/* composite */
	cxdev->input = 1;
	cxdev->videodev->tvnorms = V4L2_STD_ALL;
	cxdev->norm = V4L2_STD_PAL;

	/* TODO: setup audio samples insertion */

	ret = v4l2_subdev_call(cxdev->cx25840, core, s_io_pin_config,
			       ARRAY_SIZE(cxusub_medion_pin_config),
			       cxusub_medion_pin_config);
	if (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 pin config failed (%d)\n", ret);

	/* make sure that we aren't in radio mode */
	v4l2_subdev_call(cxdev->tda9887, video, s_std, cxdev->norm);
	v4l2_subdev_call(cxdev->tuner, video, s_std, cxdev->norm);
	v4l2_subdev_call(cxdev->cx25840, video, s_std, cxdev->norm);

	memset(&subfmt, 0, sizeof(subfmt));
	subfmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	subfmt.format.width = cxdev->width;
	subfmt.format.height = cxdev->height;
	subfmt.format.code = MEDIA_BUS_FMT_FIXED;
	subfmt.format.field = V4L2_FIELD_SEQ_TB;
	subfmt.format.colorspace = V4L2_COLORSPACE_SMPTE170M;

	ret = v4l2_subdev_call(cxdev->cx25840, pad, set_fmt, NULL, &subfmt);
	if (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "cx25840 format set failed (%d)\n", ret);

	if (ret == 0) {
		cxdev->width = subfmt.format.width;
		cxdev->height = subfmt.format.height;
	}

	return 0;
}