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
struct vpif_capture_config {struct vpif_capture_chan_config* chan_config; } ;
struct vpif_capture_chan_config {unsigned int input_count; } ;
struct video_device {int dummy; } ;
struct file {int dummy; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; } ;
struct channel_obj {size_t channel_id; struct common_obj* common; } ;
struct TYPE_2__ {struct vpif_capture_config* platform_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t VPIF_VIDEO_INDEX ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 TYPE_1__* vpif_dev ; 
 int vpif_set_input (struct vpif_capture_config*,struct channel_obj*,unsigned int) ; 

__attribute__((used)) static int vpif_s_input(struct file *file, void *priv, unsigned int index)
{
	struct vpif_capture_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct vpif_capture_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channel_id];

	if (index >= chan_cfg->input_count)
		return -EINVAL;

	if (vb2_is_busy(&common->buffer_queue))
		return -EBUSY;

	return vpif_set_input(config, ch, index);
}