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
struct vpif_display_chan_config {size_t output_count; TYPE_1__* outputs; } ;
struct video_device {int dummy; } ;
struct v4l2_output {size_t index; } ;
struct file {int dummy; } ;
struct channel_obj {size_t channel_id; } ;
struct TYPE_4__ {struct vpif_display_config* platform_data; } ;
struct TYPE_3__ {struct v4l2_output output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* vpif_dev ; 

__attribute__((used)) static int vpif_enum_output(struct file *file, void *fh,
				struct v4l2_output *output)
{

	struct vpif_display_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct vpif_display_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channel_id];
	if (output->index >= chan_cfg->output_count) {
		vpif_dbg(1, debug, "Invalid output index\n");
		return -EINVAL;
	}

	*output = chan_cfg->outputs[output->index].output;
	return 0;
}