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
struct TYPE_5__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct cx25821_channel {int width; int height; TYPE_1__* fmt; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {int depth; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 struct cx25821_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int cx25821_vidioc_g_fmt_vid_cap(struct file *file, void *priv,
				 struct v4l2_format *f)
{
	struct cx25821_channel *chan = video_drvdata(file);

	f->fmt.pix.width = chan->width;
	f->fmt.pix.height = chan->height;
	f->fmt.pix.field = chan->field;
	f->fmt.pix.pixelformat = chan->fmt->fourcc;
	f->fmt.pix.bytesperline = (chan->width * chan->fmt->depth) >> 3;
	f->fmt.pix.sizeimage = chan->height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}