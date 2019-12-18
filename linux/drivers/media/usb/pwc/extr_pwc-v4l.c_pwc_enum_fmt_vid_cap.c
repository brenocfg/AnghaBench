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
struct pwc_device {int type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_PWC1 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_PWC2 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV420 ; 
 struct pwc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int pwc_enum_fmt_vid_cap(struct file *file, void *fh, struct v4l2_fmtdesc *f)
{
	struct pwc_device *pdev = video_drvdata(file);

	/* We only support two format: the raw format, and YUV */
	switch (f->index) {
	case 0:
		/* RAW format */
		f->pixelformat = pdev->type <= 646 ? V4L2_PIX_FMT_PWC1 : V4L2_PIX_FMT_PWC2;
		break;
	case 1:
		f->pixelformat = V4L2_PIX_FMT_YUV420;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}