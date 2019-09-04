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
struct vim2m_fmt {int depth; } ;
struct TYPE_3__ {int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;

/* Variables and functions */
 int DIM_ALIGN_MASK ; 
 int MAX_H ; 
 int MAX_W ; 
 int MIN_H ; 
 int MIN_W ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 

__attribute__((used)) static int vidioc_try_fmt(struct v4l2_format *f, struct vim2m_fmt *fmt)
{
	/* V4L2 specification suggests the driver corrects the format struct
	 * if any of the dimensions is unsupported */
	if (f->fmt.pix.height < MIN_H)
		f->fmt.pix.height = MIN_H;
	else if (f->fmt.pix.height > MAX_H)
		f->fmt.pix.height = MAX_H;

	if (f->fmt.pix.width < MIN_W)
		f->fmt.pix.width = MIN_W;
	else if (f->fmt.pix.width > MAX_W)
		f->fmt.pix.width = MAX_W;

	f->fmt.pix.width &= ~DIM_ALIGN_MASK;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.field = V4L2_FIELD_NONE;

	return 0;
}