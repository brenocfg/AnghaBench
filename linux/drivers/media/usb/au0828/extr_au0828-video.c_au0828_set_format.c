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
struct TYPE_3__ {int width; int height; scalar_t__ pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct au0828_dev {int width; int height; int frame_size; int field_size; int bytesperline; scalar_t__ stream_state; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ STREAM_ON ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_PIX_FMT_UYVY ; 
 unsigned int VIDIOC_TRY_FMT ; 
 int /*<<< orphan*/  au0828_analog_stream_enable (struct au0828_dev*) ; 
 int au0828_stream_interrupt (struct au0828_dev*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int au0828_set_format(struct au0828_dev *dev, unsigned int cmd,
			     struct v4l2_format *format)
{
	int ret;
	int width = format->fmt.pix.width;
	int height = format->fmt.pix.height;

	/* If they are demanding a format other than the one we support,
	   bail out (tvtime asks for UYVY and then retries with YUYV) */
	if (format->fmt.pix.pixelformat != V4L2_PIX_FMT_UYVY)
		return -EINVAL;

	/* format->fmt.pix.width only support 720 and height 480 */
	if (width != 720)
		width = 720;
	if (height != 480)
		height = 480;

	format->fmt.pix.width = width;
	format->fmt.pix.height = height;
	format->fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	format->fmt.pix.bytesperline = width * 2;
	format->fmt.pix.sizeimage = width * height * 2;
	format->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	format->fmt.pix.field = V4L2_FIELD_INTERLACED;

	if (cmd == VIDIOC_TRY_FMT)
		return 0;

	/* maybe set new image format, driver current only support 720*480 */
	dev->width = width;
	dev->height = height;
	dev->frame_size = width * height * 2;
	dev->field_size = width * height;
	dev->bytesperline = width * 2;

	if (dev->stream_state == STREAM_ON) {
		dprintk(1, "VIDIOC_SET_FMT: interrupting stream!\n");
		ret = au0828_stream_interrupt(dev);
		if (ret != 0) {
			dprintk(1, "error interrupting video stream!\n");
			return ret;
		}
	}

	au0828_analog_stream_enable(dev);

	return 0;
}