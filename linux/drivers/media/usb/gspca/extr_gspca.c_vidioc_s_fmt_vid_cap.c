#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  priv; } ;
struct TYPE_7__ {TYPE_4__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct TYPE_6__ {TYPE_4__* cam_mode; } ;
struct gspca_dev {int curr_mode; TYPE_2__ cam; TYPE_4__ pixfmt; TYPE_1__* sd_desc; int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;
struct TYPE_5__ {scalar_t__ try_fmt; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int try_fmt_vid_cap (struct gspca_dev*,struct v4l2_format*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct gspca_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *_priv,
				struct v4l2_format *fmt)
{
	struct gspca_dev *gspca_dev = video_drvdata(file);
	u32 priv = fmt->fmt.pix.priv;
	int mode;

	if (vb2_is_busy(&gspca_dev->queue))
		return -EBUSY;

	mode = try_fmt_vid_cap(gspca_dev, fmt);
	if (mode < 0)
		return -EINVAL;

	gspca_dev->curr_mode = mode;
	if (gspca_dev->sd_desc->try_fmt)
		/* subdriver try_fmt can modify format parameters */
		gspca_dev->pixfmt = fmt->fmt.pix;
	else
		gspca_dev->pixfmt = gspca_dev->cam.cam_mode[mode];
	/* some drivers use priv internally, so keep the original value */
	fmt->fmt.pix.priv = priv;
	return 0;
}