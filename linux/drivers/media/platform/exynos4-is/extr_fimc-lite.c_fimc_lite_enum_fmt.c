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
struct fimc_fmt {int /*<<< orphan*/  fourcc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct fimc_fmt*) ; 
 int EINVAL ; 
 struct fimc_fmt* fimc_lite_formats ; 

__attribute__((used)) static int fimc_lite_enum_fmt(struct file *file, void *priv,
			      struct v4l2_fmtdesc *f)
{
	const struct fimc_fmt *fmt;

	if (f->index >= ARRAY_SIZE(fimc_lite_formats))
		return -EINVAL;

	fmt = &fimc_lite_formats[f->index];
	f->pixelformat = fmt->fourcc;

	return 0;
}