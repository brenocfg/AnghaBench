#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_dv_timings {TYPE_3__ bt; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_cropcap {scalar_t__ type; int /*<<< orphan*/  pixelaspect; TYPE_2__ defrect; TYPE_1__ bounds; } ;
struct file {int dummy; } ;
struct cobalt_stream {int input; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct v4l2_dv_timings cea1080p60 ; 
 int /*<<< orphan*/  g_dv_timings ; 
 int /*<<< orphan*/  v4l2_dv_timings_aspect_ratio (struct v4l2_dv_timings*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_cropcap(struct file *file, void *fh, struct v4l2_cropcap *cc)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_dv_timings timings;
	int err = 0;

	if (cc->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (s->input == 1)
		timings = cea1080p60;
	else
		err = v4l2_subdev_call(s->sd, video, g_dv_timings, &timings);
	if (!err) {
		cc->bounds.width = cc->defrect.width = timings.bt.width;
		cc->bounds.height = cc->defrect.height = timings.bt.height;
		cc->pixelaspect = v4l2_dv_timings_aspect_ratio(&timings);
	}
	return err;
}