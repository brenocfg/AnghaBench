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
struct TYPE_4__ {int sizeimage; int /*<<< orphan*/  field; scalar_t__ colorspace; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int ts_packet_size; int ts_packet_count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct cx23885_dev {TYPE_3__ ts1; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx23885_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cx23885_dev *dev = video_drvdata(file);

	f->fmt.pix.pixelformat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.colorspace   = 0;
	f->fmt.pix.field        = V4L2_FIELD_INTERLACED;
	dprintk(1, "VIDIOC_TRY_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	return 0;
}