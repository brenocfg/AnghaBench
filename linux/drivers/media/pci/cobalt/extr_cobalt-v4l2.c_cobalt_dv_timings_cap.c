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
struct v4l2_dv_timings_cap {scalar_t__ pad; } ;
struct file {int dummy; } ;
struct cobalt_stream {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dv_timings_cap ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings_cap*) ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_dv_timings_cap(struct file *file, void *priv_fh,
				    struct v4l2_dv_timings_cap *cap)
{
	struct cobalt_stream *s = video_drvdata(file);

	cap->pad = 0;
	return v4l2_subdev_call(s->sd,
			pad, dv_timings_cap, cap);
}