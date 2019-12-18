#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int width; int /*<<< orphan*/  height; } ;
struct v4l2_dv_timings {TYPE_1__ bt; } ;
struct file {int dummy; } ;
struct cobalt_stream {int input; int width; int stride; int bpp; int /*<<< orphan*/  height; struct v4l2_dv_timings timings; int /*<<< orphan*/  sd; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int EBUSY ; 
 struct v4l2_dv_timings cea1080p60 ; 
 int /*<<< orphan*/  s_dv_timings ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings*,struct v4l2_dv_timings*,int /*<<< orphan*/ ,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_s_dv_timings(struct file *file, void *priv_fh,
				    struct v4l2_dv_timings *timings)
{
	struct cobalt_stream *s = video_drvdata(file);
	int err;

	if (s->input == 1) {
		*timings = cea1080p60;
		return 0;
	}

	if (v4l2_match_dv_timings(timings, &s->timings, 0, true))
		return 0;

	if (vb2_is_busy(&s->q))
		return -EBUSY;

	err = v4l2_subdev_call(s->sd,
			video, s_dv_timings, timings);
	if (!err) {
		s->timings = *timings;
		s->width = timings->bt.width;
		s->height = timings->bt.height;
		s->stride = timings->bt.width * s->bpp;
	}
	return err;
}