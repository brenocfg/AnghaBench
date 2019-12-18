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
struct v4l2_fmtdesc {int /*<<< orphan*/  pixelformat; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 

__attribute__((used)) static int pvr2_enum_fmt_vid_cap(struct file *file, void *priv, struct v4l2_fmtdesc *fd)
{
	/* Only one format is supported: MPEG. */
	if (fd->index)
		return -EINVAL;

	fd->pixelformat = V4L2_PIX_FMT_MPEG;
	return 0;
}