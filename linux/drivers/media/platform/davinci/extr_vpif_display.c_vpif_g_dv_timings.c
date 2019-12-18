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
struct vpif_display_config {struct vpif_display_chan_config* chan_config; } ;
struct vpif_display_chan_config {TYPE_1__* outputs; } ;
struct v4l2_dv_timings {int dummy; } ;
struct video_obj {struct v4l2_dv_timings dv_timings; } ;
struct video_device {int dummy; } ;
struct v4l2_output {scalar_t__ capabilities; } ;
struct file {int dummy; } ;
struct channel_obj {size_t channel_id; size_t output_idx; struct video_obj video; } ;
struct TYPE_4__ {struct vpif_display_config* platform_data; } ;
struct TYPE_3__ {struct v4l2_output output; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ V4L2_OUT_CAP_DV_TIMINGS ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 TYPE_2__* vpif_dev ; 

__attribute__((used)) static int vpif_g_dv_timings(struct file *file, void *priv,
		struct v4l2_dv_timings *timings)
{
	struct vpif_display_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct vpif_display_chan_config *chan_cfg;
	struct video_obj *vid_ch = &ch->video;
	struct v4l2_output output;

	if (!config->chan_config[ch->channel_id].outputs)
		goto error;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outputs[ch->output_idx].output;

	if (output.capabilities != V4L2_OUT_CAP_DV_TIMINGS)
		goto error;

	*timings = vid_ch->dv_timings;

	return 0;
error:
	return -ENODATA;
}