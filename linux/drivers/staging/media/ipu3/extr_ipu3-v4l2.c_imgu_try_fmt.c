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
struct v4l2_pix_format_mplane {TYPE_1__* plane_fmt; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_2__ fmt; } ;
struct imgu_fmt {int /*<<< orphan*/  fourcc; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reserved; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VID_CAPTURE ; 
 int /*<<< orphan*/  VID_OUTPUT ; 
 struct imgu_fmt* find_format (struct v4l2_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imgu_try_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pixm = &f->fmt.pix_mp;
	const struct imgu_fmt *fmt;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		fmt = find_format(f, VID_CAPTURE);
	else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt = find_format(f, VID_OUTPUT);
	else
		return -EINVAL;

	pixm->pixelformat = fmt->fourcc;

	memset(pixm->plane_fmt[0].reserved, 0,
	       sizeof(pixm->plane_fmt[0].reserved));

	return 0;
}