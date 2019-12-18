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
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  index; } ;
struct fimc_fmt {int /*<<< orphan*/  fourcc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMT_FLAGS_CAM ; 
 int FMT_FLAGS_M2M ; 
 struct fimc_fmt* fimc_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_cap_enum_fmt(struct file *file, void *priv,
			     struct v4l2_fmtdesc *f)
{
	struct fimc_fmt *fmt;

	fmt = fimc_find_format(NULL, NULL, FMT_FLAGS_CAM | FMT_FLAGS_M2M,
			       f->index);
	if (!fmt)
		return -EINVAL;
	f->pixelformat = fmt->fourcc;
	return 0;
}