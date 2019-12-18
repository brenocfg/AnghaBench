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
struct sun6i_video {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int sun6i_video_try_fmt (struct sun6i_video*,struct v4l2_format*) ; 
 struct sun6i_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct sun6i_video *video = video_drvdata(file);

	return sun6i_video_try_fmt(video, f);
}