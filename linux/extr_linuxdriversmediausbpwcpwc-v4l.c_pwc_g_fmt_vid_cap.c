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
struct v4l2_format {scalar_t__ type; } ;
struct pwc_device {int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PWC_DEBUG_IOCTL (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  pwc_vidioc_fill_fmt (struct v4l2_format*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pwc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int pwc_g_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
	struct pwc_device *pdev = video_drvdata(file);

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	PWC_DEBUG_IOCTL("ioctl(VIDIOC_G_FMT) return size %dx%d\n",
			pdev->width, pdev->height);
	pwc_vidioc_fill_fmt(f, pdev->width, pdev->height, pdev->pixfmt);
	return 0;
}