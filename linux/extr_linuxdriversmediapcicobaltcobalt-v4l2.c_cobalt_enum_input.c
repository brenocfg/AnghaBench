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
struct v4l2_input {int index; int /*<<< orphan*/  status; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct cobalt_stream {int video_channel; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  g_input_status ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_enum_input(struct file *file, void *priv_fh,
				 struct v4l2_input *inp)
{
	struct cobalt_stream *s = video_drvdata(file);

	if (inp->index > 1)
		return -EINVAL;
	if (inp->index == 0)
		snprintf(inp->name, sizeof(inp->name),
				"HDMI-%d", s->video_channel);
	else
		snprintf(inp->name, sizeof(inp->name),
				"Generator-%d", s->video_channel);
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
	if (inp->index == 1)
		return 0;
	return v4l2_subdev_call(s->sd,
			video, g_input_status, &inp->status);
}