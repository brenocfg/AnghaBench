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
struct v4l2_fmtdesc {scalar_t__ index; scalar_t__ flags; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV422P ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_enum_fmt_vid_out(struct file *file, void  *priv,
					struct v4l2_fmtdesc *fmt)
{
	if (fmt->index != 0)
		return -EINVAL;

	/* Fill in the information about format */
	fmt->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	strcpy(fmt->description, "YCbCr4:2:2 YC Planar");
	fmt->pixelformat = V4L2_PIX_FMT_YUV422P;
	fmt->flags = 0;
	return 0;
}