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
struct sun6i_video {struct v4l2_format fmt; } ;

/* Variables and functions */
 int sun6i_video_try_fmt (struct sun6i_video*,struct v4l2_format*) ; 

__attribute__((used)) static int sun6i_video_set_fmt(struct sun6i_video *video, struct v4l2_format *f)
{
	int ret;

	ret = sun6i_video_try_fmt(video, f);
	if (ret)
		return ret;

	video->fmt = *f;

	return 0;
}