#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct vpif_display_config {struct vpif_display_chan_config* chan_config; } ;
struct vpif_display_chan_config {TYPE_1__* outputs; } ;
struct video_device {int dummy; } ;
struct v4l2_output {scalar_t__ capabilities; } ;
struct file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  width; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_11__ {TYPE_3__ pix; } ;
struct TYPE_12__ {TYPE_4__ fmt; } ;
struct common_obj {TYPE_5__ fmt; int /*<<< orphan*/  buffer_queue; } ;
struct TYPE_9__ {int stdid; int /*<<< orphan*/  dv_timings; } ;
struct channel_obj {size_t channel_id; size_t output_idx; TYPE_2__ video; struct common_obj* common; } ;
struct TYPE_14__ {struct vpif_display_config* platform_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_8__ {struct v4l2_output output; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODATA ; 
 scalar_t__ V4L2_OUT_CAP_STD ; 
 int VPIF_V4L2_STD ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  s_std_output ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 TYPE_7__* vpif_dev ; 
 int /*<<< orphan*/  vpif_err (char*) ; 
 TYPE_6__ vpif_obj ; 
 scalar_t__ vpif_update_resolution (struct channel_obj*) ; 

__attribute__((used)) static int vpif_s_std(struct file *file, void *priv, v4l2_std_id std_id)
{
	struct vpif_display_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct vpif_display_chan_config *chan_cfg;
	struct v4l2_output output;
	int ret;

	if (!config->chan_config[ch->channel_id].outputs)
		return -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outputs[ch->output_idx].output;
	if (output.capabilities != V4L2_OUT_CAP_STD)
		return -ENODATA;

	if (vb2_is_busy(&common->buffer_queue))
		return -EBUSY;


	if (!(std_id & VPIF_V4L2_STD))
		return -EINVAL;

	/* Call encoder subdevice function to set the standard */
	ch->video.stdid = std_id;
	memset(&ch->video.dv_timings, 0, sizeof(ch->video.dv_timings));
	/* Get the information about the standard */
	if (vpif_update_resolution(ch))
		return -EINVAL;

	common->fmt.fmt.pix.bytesperline = common->fmt.fmt.pix.width;

	ret = v4l2_device_call_until_err(&vpif_obj.v4l2_dev, 1, video,
						s_std_output, std_id);
	if (ret < 0) {
		vpif_err("Failed to set output standard\n");
		return ret;
	}

	ret = v4l2_device_call_until_err(&vpif_obj.v4l2_dev, 1, video,
							s_std, std_id);
	if (ret < 0)
		vpif_err("Failed to set standard for sub devices\n");
	return ret;
}