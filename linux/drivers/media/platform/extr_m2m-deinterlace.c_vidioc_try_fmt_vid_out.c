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
struct TYPE_3__ {scalar_t__ field; scalar_t__ colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct deinterlace_fmt {int types; } ;

/* Variables and functions */
 int MEM2MEM_OUTPUT ; 
 scalar_t__ V4L2_COLORSPACE_REC709 ; 
 scalar_t__ V4L2_FIELD_SEQ_BT ; 
 scalar_t__ V4L2_FIELD_SEQ_TB ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV420 ; 
 struct deinterlace_fmt* find_format (struct v4l2_format*) ; 
 int vidioc_try_fmt (struct v4l2_format*,struct deinterlace_fmt*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_out(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct deinterlace_fmt *fmt;

	fmt = find_format(f);
	if (!fmt || !(fmt->types & MEM2MEM_OUTPUT))
		f->fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;

	if (!f->fmt.pix.colorspace)
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	if (f->fmt.pix.field != V4L2_FIELD_SEQ_TB &&
	    f->fmt.pix.field != V4L2_FIELD_SEQ_BT)
		f->fmt.pix.field = V4L2_FIELD_SEQ_TB;

	return vidioc_try_fmt(f, fmt);
}