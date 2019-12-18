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
typedef  size_t u32 ;
struct v4l2_input {size_t index; size_t status; int /*<<< orphan*/  capabilities; } ;
struct file {int dummy; } ;
struct dvb_usb_device {TYPE_1__* udev; struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {size_t input; int /*<<< orphan*/  cx25840; } ;
struct TYPE_4__ {struct v4l2_input input; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CXUSB_INPUT_CNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_IN_CAP_STD ; 
 TYPE_2__* cxusb_medion_inputs ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  g_input_status ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  video ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cxusb_medion_enum_input(struct file *file, void *fh,
				   struct v4l2_input *inp)
{
	struct dvb_usb_device *dvbdev = video_drvdata(file);
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	u32 index = inp->index;

	if (index >= CXUSB_INPUT_CNT)
		return -EINVAL;

	*inp = cxusb_medion_inputs[index].input;
	inp->index = index;
	inp->capabilities |= V4L2_IN_CAP_STD;

	if (index == cxdev->input) {
		int ret;
		u32 status = 0;

		ret = v4l2_subdev_call(cxdev->cx25840, video, g_input_status,
				       &status);
		if (ret != 0)
			dev_warn(&dvbdev->udev->dev,
				 "cx25840 input status query failed (%d)\n",
				 ret);
		else
			inp->status = status;
	}

	return 0;
}