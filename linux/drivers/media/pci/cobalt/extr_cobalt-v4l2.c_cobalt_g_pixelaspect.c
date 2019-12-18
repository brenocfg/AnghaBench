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
struct v4l2_fract {int dummy; } ;
struct v4l2_dv_timings {int dummy; } ;
struct file {int dummy; } ;
struct cobalt_stream {int input; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct v4l2_dv_timings cea1080p60 ; 
 int /*<<< orphan*/  g_dv_timings ; 
 struct v4l2_fract v4l2_dv_timings_aspect_ratio (struct v4l2_dv_timings*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_g_pixelaspect(struct file *file, void *fh,
				int type, struct v4l2_fract *f)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_dv_timings timings;
	int err = 0;

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (s->input == 1)
		timings = cea1080p60;
	else
		err = v4l2_subdev_call(s->sd, video, g_dv_timings, &timings);
	if (!err)
		*f = v4l2_dv_timings_aspect_ratio(&timings);
	return err;
}