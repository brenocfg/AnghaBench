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
struct TYPE_5__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_3__ fmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwMaxVideoFrameSize; } ;
struct uvc_streaming {scalar_t__ type; int /*<<< orphan*/  mutex; TYPE_1__ ctrl; struct uvc_frame* cur_frame; struct uvc_format* cur_format; } ;
struct uvc_frame {int /*<<< orphan*/  wHeight; int /*<<< orphan*/  wWidth; } ;
struct uvc_format {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  fcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_v4l2_get_bytesperline (struct uvc_format*,struct uvc_frame*) ; 

__attribute__((used)) static int uvc_v4l2_get_format(struct uvc_streaming *stream,
	struct v4l2_format *fmt)
{
	struct uvc_format *format;
	struct uvc_frame *frame;
	int ret = 0;

	if (fmt->type != stream->type)
		return -EINVAL;

	mutex_lock(&stream->mutex);
	format = stream->cur_format;
	frame = stream->cur_frame;

	if (format == NULL || frame == NULL) {
		ret = -EINVAL;
		goto done;
	}

	fmt->fmt.pix.pixelformat = format->fcc;
	fmt->fmt.pix.width = frame->wWidth;
	fmt->fmt.pix.height = frame->wHeight;
	fmt->fmt.pix.field = V4L2_FIELD_NONE;
	fmt->fmt.pix.bytesperline = uvc_v4l2_get_bytesperline(format, frame);
	fmt->fmt.pix.sizeimage = stream->ctrl.dwMaxVideoFrameSize;
	fmt->fmt.pix.colorspace = format->colorspace;

done:
	mutex_unlock(&stream->mutex);
	return ret;
}