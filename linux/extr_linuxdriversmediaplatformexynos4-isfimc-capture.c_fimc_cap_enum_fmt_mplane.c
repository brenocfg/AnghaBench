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
struct v4l2_fmtdesc {scalar_t__ pixelformat; int /*<<< orphan*/  flags; int /*<<< orphan*/  description; int /*<<< orphan*/  index; } ;
struct fimc_fmt {scalar_t__ fourcc; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMT_FLAGS_CAM ; 
 int FMT_FLAGS_M2M ; 
 scalar_t__ MEDIA_BUS_FMT_JPEG_1X8 ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 struct fimc_fmt* fimc_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fimc_cap_enum_fmt_mplane(struct file *file, void *priv,
				    struct v4l2_fmtdesc *f)
{
	struct fimc_fmt *fmt;

	fmt = fimc_find_format(NULL, NULL, FMT_FLAGS_CAM | FMT_FLAGS_M2M,
			       f->index);
	if (!fmt)
		return -EINVAL;
	strncpy(f->description, fmt->name, sizeof(f->description) - 1);
	f->pixelformat = fmt->fourcc;
	if (fmt->fourcc == MEDIA_BUS_FMT_JPEG_1X8)
		f->flags |= V4L2_FMT_FLAG_COMPRESSED;
	return 0;
}