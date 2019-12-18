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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vpif_display_config {struct vpif_display_chan_config* chan_config; } ;
struct vpif_display_chan_config {TYPE_1__* outputs; } ;
struct video_device {int dummy; } ;
struct v4l2_output {scalar_t__ capabilities; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  stdid; } ;
struct channel_obj {size_t channel_id; size_t output_idx; TYPE_2__ video; } ;
struct TYPE_6__ {struct vpif_display_config* platform_data; } ;
struct TYPE_4__ {struct v4l2_output output; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ V4L2_OUT_CAP_STD ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 TYPE_3__* vpif_dev ; 

__attribute__((used)) static int vpif_g_std(struct file *file, void *priv, v4l2_std_id *std)
{
	struct vpif_display_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct vpif_display_chan_config *chan_cfg;
	struct v4l2_output output;

	if (!config->chan_config[ch->channel_id].outputs)
		return -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outputs[ch->output_idx].output;
	if (output.capabilities != V4L2_OUT_CAP_STD)
		return -ENODATA;

	*std = ch->video.stdid;
	return 0;
}