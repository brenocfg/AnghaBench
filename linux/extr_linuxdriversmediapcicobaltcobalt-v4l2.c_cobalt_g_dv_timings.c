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
struct v4l2_dv_timings {int dummy; } ;
struct file {int dummy; } ;
struct cobalt_stream {int input; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 struct v4l2_dv_timings cea1080p60 ; 
 int /*<<< orphan*/  g_dv_timings ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_g_dv_timings(struct file *file, void *priv_fh,
				    struct v4l2_dv_timings *timings)
{
	struct cobalt_stream *s = video_drvdata(file);

	if (s->input == 1) {
		*timings = cea1080p60;
		return 0;
	}
	return v4l2_subdev_call(s->sd,
			video, g_dv_timings, timings);
}