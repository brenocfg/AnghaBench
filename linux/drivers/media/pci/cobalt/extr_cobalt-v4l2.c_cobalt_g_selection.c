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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_dv_timings {TYPE_2__ bt; } ;
struct file {int dummy; } ;
struct cobalt_stream {int input; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct v4l2_dv_timings cea1080p60 ; 
 int /*<<< orphan*/  g_dv_timings ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_g_selection(struct file *file, void *fh,
			      struct v4l2_selection *sel)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct v4l2_dv_timings timings;
	int err = 0;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (s->input == 1)
		timings = cea1080p60;
	else
		err = v4l2_subdev_call(s->sd, video, g_dv_timings, &timings);

	if (err)
		return err;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = timings.bt.width;
		sel->r.height = timings.bt.height;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}