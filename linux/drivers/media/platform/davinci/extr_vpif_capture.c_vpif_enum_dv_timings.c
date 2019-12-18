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
struct vpif_capture_config {struct vpif_capture_chan_config* chan_config; } ;
struct vpif_capture_chan_config {TYPE_1__* inputs; } ;
struct video_device {int dummy; } ;
struct v4l2_input {scalar_t__ capabilities; } ;
struct v4l2_enum_dv_timings {scalar_t__ pad; } ;
struct file {int dummy; } ;
struct channel_obj {size_t channel_id; size_t input_idx; int /*<<< orphan*/  sd; } ;
struct TYPE_4__ {struct vpif_capture_config* platform_data; } ;
struct TYPE_3__ {struct v4l2_input input; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 scalar_t__ V4L2_IN_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  enum_dv_timings ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_enum_dv_timings*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 TYPE_2__* vpif_dev ; 

__attribute__((used)) static int
vpif_enum_dv_timings(struct file *file, void *priv,
		     struct v4l2_enum_dv_timings *timings)
{
	struct vpif_capture_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct vpif_capture_chan_config *chan_cfg;
	struct v4l2_input input;
	int ret;

	if (!config->chan_config[ch->channel_id].inputs)
		return -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabilities != V4L2_IN_CAP_DV_TIMINGS)
		return -ENODATA;

	timings->pad = 0;

	ret = v4l2_subdev_call(ch->sd, pad, enum_dv_timings, timings);
	if (ret == -ENOIOCTLCMD || ret == -ENODEV)
		return -EINVAL;

	return ret;
}