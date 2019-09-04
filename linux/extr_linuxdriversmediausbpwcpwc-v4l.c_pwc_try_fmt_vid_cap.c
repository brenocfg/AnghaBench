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
struct pwc_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int pwc_vidioc_try_fmt (struct pwc_device*,struct v4l2_format*) ; 
 struct pwc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int pwc_try_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
	struct pwc_device *pdev = video_drvdata(file);

	return pwc_vidioc_try_fmt(pdev, f);
}