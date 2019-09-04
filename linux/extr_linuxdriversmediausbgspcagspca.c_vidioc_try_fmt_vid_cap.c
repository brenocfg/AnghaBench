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
struct v4l2_format {int dummy; } ;
struct gspca_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ try_fmt_vid_cap (struct gspca_dev*,struct v4l2_format*) ; 
 struct gspca_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file,
			      void *priv,
			      struct v4l2_format *fmt)
{
	struct gspca_dev *gspca_dev = video_drvdata(file);

	if (try_fmt_vid_cap(gspca_dev, fmt) < 0)
		return -EINVAL;
	return 0;
}