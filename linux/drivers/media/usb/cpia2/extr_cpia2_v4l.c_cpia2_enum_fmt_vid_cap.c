#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MJPEG ; 

__attribute__((used)) static int cpia2_enum_fmt_vid_cap(struct file *file, void *fh,
					    struct v4l2_fmtdesc *f)
{
	if (f->index > 1)
		return -EINVAL;

	if (f->index == 0)
		f->pixelformat = V4L2_PIX_FMT_MJPEG;
	else
		f->pixelformat = V4L2_PIX_FMT_JPEG;
	return 0;
}