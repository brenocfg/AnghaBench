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
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  scalar_t__ u32 ;
struct dvb_usb_device {TYPE_1__* udev; } ;
struct cxusb_medion_dev {scalar_t__ input; int /*<<< orphan*/  cx25840; int /*<<< orphan*/  norm; struct dvb_usb_device* dvbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_FIELD_SEQ_TB ; 
 scalar_t__ cxusb_medion_norm2field_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_std ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static u32 cxusb_medion_field_order(struct cxusb_medion_dev *cxdev)
{
	struct dvb_usb_device *dvbdev = cxdev->dvbdev;
	u32 field;
	int ret;
	v4l2_std_id norm;

	/* TV tuner is PAL-only so it is always TB */
	if (cxdev->input == 0)
		return V4L2_FIELD_SEQ_TB;

	field = cxusb_medion_norm2field_order(cxdev->norm);
	if (field != V4L2_FIELD_NONE)
		return field;

	ret = v4l2_subdev_call(cxdev->cx25840, video, g_std, &norm);
	if (ret != 0) {
		cxusb_vprintk(dvbdev, OPS,
			      "cannot get current standard for input %u\n",
			      (unsigned int)cxdev->input);
	} else {
		field = cxusb_medion_norm2field_order(norm);
		if (field != V4L2_FIELD_NONE)
			return field;
	}

	dev_warn(&dvbdev->udev->dev,
		 "cannot determine field order for the current standard setup and received signal, using TB\n");
	return V4L2_FIELD_SEQ_TB;
}