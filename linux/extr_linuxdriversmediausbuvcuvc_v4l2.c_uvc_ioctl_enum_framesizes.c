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
struct TYPE_2__ {scalar_t__ width; scalar_t__ height; } ;
struct v4l2_frmsizeenum {scalar_t__ pixel_format; unsigned int index; TYPE_1__ discrete; int /*<<< orphan*/  type; } ;
struct uvc_streaming {unsigned int nformats; struct uvc_format* format; } ;
struct uvc_frame {scalar_t__ wWidth; scalar_t__ wHeight; } ;
struct uvc_format {scalar_t__ fcc; unsigned int nframes; struct uvc_frame* frame; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 

__attribute__((used)) static int uvc_ioctl_enum_framesizes(struct file *file, void *fh,
				     struct v4l2_frmsizeenum *fsize)
{
	struct uvc_fh *handle = fh;
	struct uvc_streaming *stream = handle->stream;
	struct uvc_format *format = NULL;
	struct uvc_frame *frame = NULL;
	unsigned int index;
	unsigned int i;

	/* Look for the given pixel format */
	for (i = 0; i < stream->nformats; i++) {
		if (stream->format[i].fcc == fsize->pixel_format) {
			format = &stream->format[i];
			break;
		}
	}
	if (format == NULL)
		return -EINVAL;

	/* Skip duplicate frame sizes */
	for (i = 0, index = 0; i < format->nframes; i++) {
		if (frame && frame->wWidth == format->frame[i].wWidth &&
		    frame->wHeight == format->frame[i].wHeight)
			continue;
		frame = &format->frame[i];
		if (index == fsize->index)
			break;
		index++;
	}

	if (i == format->nframes)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = frame->wWidth;
	fsize->discrete.height = frame->wHeight;
	return 0;
}