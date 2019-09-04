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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  pixelformat; } ;
struct rga_fmt {int /*<<< orphan*/  fourcc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NUM_FORMATS ; 
 struct rga_fmt* formats ; 

__attribute__((used)) static int vidioc_enum_fmt(struct file *file, void *prv, struct v4l2_fmtdesc *f)
{
	struct rga_fmt *fmt;

	if (f->index >= NUM_FORMATS)
		return -EINVAL;

	fmt = &formats[f->index];
	f->pixelformat = fmt->fourcc;

	return 0;
}