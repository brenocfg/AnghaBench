#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {int dummy; } ;
struct TYPE_9__ {int field; } ;
struct TYPE_8__ {TYPE_4__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_3__ fmt; } ;
struct isp_video_fh {struct v4l2_format format; } ;
struct isp_video {scalar_t__ type; int /*<<< orphan*/  mutex; TYPE_2__* isp; } ;
struct file {int dummy; } ;
struct TYPE_6__ {struct isp_video video_out; } ;
struct TYPE_7__ {TYPE_1__ isp_ccdc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_FIELD_ALTERNATE 136 
#define  V4L2_FIELD_BOTTOM 135 
#define  V4L2_FIELD_INTERLACED 134 
#define  V4L2_FIELD_INTERLACED_BT 133 
#define  V4L2_FIELD_INTERLACED_TB 132 
#define  V4L2_FIELD_NONE 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  isp_video_mbus_to_pix (struct isp_video*,struct v4l2_mbus_framefmt*,TYPE_4__*) ; 
 int /*<<< orphan*/  isp_video_pix_to_mbus (TYPE_4__*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* to_isp_video_fh (void*) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
isp_video_set_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct isp_video_fh *vfh = to_isp_video_fh(fh);
	struct isp_video *video = video_drvdata(file);
	struct v4l2_mbus_framefmt fmt;

	if (format->type != video->type)
		return -EINVAL;

	/* Replace unsupported field orders with sane defaults. */
	switch (format->fmt.pix.field) {
	case V4L2_FIELD_NONE:
		/* Progressive is supported everywhere. */
		break;
	case V4L2_FIELD_ALTERNATE:
		/* ALTERNATE is not supported on output nodes. */
		if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			format->fmt.pix.field = V4L2_FIELD_NONE;
		break;
	case V4L2_FIELD_INTERLACED:
		/* The ISP has no concept of video standard, select the
		 * top-bottom order when the unqualified interlaced order is
		 * requested.
		 */
		format->fmt.pix.field = V4L2_FIELD_INTERLACED_TB;
		/* Fall-through */
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
		/* Interlaced orders are only supported at the CCDC output. */
		if (video != &video->isp->isp_ccdc.video_out)
			format->fmt.pix.field = V4L2_FIELD_NONE;
		break;
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
	case V4L2_FIELD_SEQ_TB:
	case V4L2_FIELD_SEQ_BT:
	default:
		/* All other field orders are currently unsupported, default to
		 * progressive.
		 */
		format->fmt.pix.field = V4L2_FIELD_NONE;
		break;
	}

	/* Fill the bytesperline and sizeimage fields by converting to media bus
	 * format and back to pixel format.
	 */
	isp_video_pix_to_mbus(&format->fmt.pix, &fmt);
	isp_video_mbus_to_pix(video, &fmt, &format->fmt.pix);

	mutex_lock(&video->mutex);
	vfh->format = *format;
	mutex_unlock(&video->mutex);

	return 0;
}