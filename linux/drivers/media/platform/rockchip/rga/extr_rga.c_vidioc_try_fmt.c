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
struct TYPE_3__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct rga_fmt {scalar_t__ hw_format; int depth; int /*<<< orphan*/  fourcc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int MAX_HEIGHT ; 
 int MAX_WIDTH ; 
 int MIN_HEIGHT ; 
 int MIN_WIDTH ; 
 scalar_t__ RGA_COLOR_FMT_YUV422SP ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct rga_fmt* formats ; 
 struct rga_fmt* rga_fmt_find (struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_try_fmt(struct file *file, void *prv, struct v4l2_format *f)
{
	struct rga_fmt *fmt;

	fmt = rga_fmt_find(f);
	if (!fmt) {
		fmt = &formats[0];
		f->fmt.pix.pixelformat = fmt->fourcc;
	}

	f->fmt.pix.field = V4L2_FIELD_NONE;

	if (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	if (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	if (f->fmt.pix.width < MIN_WIDTH)
		f->fmt.pix.width = MIN_WIDTH;
	if (f->fmt.pix.height < MIN_HEIGHT)
		f->fmt.pix.height = MIN_HEIGHT;

	if (fmt->hw_format >= RGA_COLOR_FMT_YUV422SP)
		f->fmt.pix.bytesperline = f->fmt.pix.width;
	else
		f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;

	f->fmt.pix.sizeimage =
		f->fmt.pix.height * (f->fmt.pix.width * fmt->depth) >> 3;

	return 0;
}