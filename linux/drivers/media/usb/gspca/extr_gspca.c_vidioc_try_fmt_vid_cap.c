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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  priv; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct gspca_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ try_fmt_vid_cap (struct gspca_dev*,struct v4l2_format*) ; 
 struct gspca_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *_priv,
				  struct v4l2_format *fmt)
{
	struct gspca_dev *gspca_dev = video_drvdata(file);
	u32 priv = fmt->fmt.pix.priv;

	if (try_fmt_vid_cap(gspca_dev, fmt) < 0)
		return -EINVAL;
	/* some drivers use priv internally, so keep the original value */
	fmt->fmt.pix.priv = priv;
	return 0;
}