#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numerator; int denominator; } ;
struct TYPE_5__ {TYPE_1__ timeperframe; } ;
struct TYPE_6__ {TYPE_2__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_3__ parm; } ;
struct pwc_device {int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  vb_queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  pwc_g_parm (struct file*,void*,struct v4l2_streamparm*) ; 
 int pwc_set_video_mode (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct pwc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int pwc_s_parm(struct file *file, void *fh,
		      struct v4l2_streamparm *parm)
{
	struct pwc_device *pdev = video_drvdata(file);
	int compression = 0;
	int ret, fps;

	if (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	/* If timeperframe == 0, then reset the framerate to the nominal value.
	   We pick a high framerate here, and let pwc_set_video_mode() figure
	   out the best match. */
	if (parm->parm.capture.timeperframe.numerator == 0 ||
	    parm->parm.capture.timeperframe.denominator == 0)
		fps = 30;
	else
		fps = parm->parm.capture.timeperframe.denominator /
		      parm->parm.capture.timeperframe.numerator;

	if (vb2_is_busy(&pdev->vb_queue))
		return -EBUSY;

	ret = pwc_set_video_mode(pdev, pdev->width, pdev->height, pdev->pixfmt,
				 fps, &compression, 0);

	pwc_g_parm(file, fh, parm);

	return ret;
}