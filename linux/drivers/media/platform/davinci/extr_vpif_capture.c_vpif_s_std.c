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
struct vpif_capture_config {struct vpif_capture_chan_config* chan_config; } ;
struct vpif_capture_chan_config {TYPE_1__* inputs; } ;
struct video_device {int dummy; } ;
struct v4l2_input {scalar_t__ capabilities; } ;
struct file {int dummy; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  dv_timings; int /*<<< orphan*/  stdid; } ;
struct channel_obj {size_t channel_id; size_t input_idx; int /*<<< orphan*/  sd; TYPE_2__ video; struct common_obj* common; } ;
struct TYPE_6__ {struct vpif_capture_config* platform_data; } ;
struct TYPE_4__ {struct v4l2_input input; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 scalar_t__ V4L2_IN_CAP_STD ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_std ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* vpif_dev ; 
 int /*<<< orphan*/  vpif_err (char*) ; 
 scalar_t__ vpif_update_std_info (struct channel_obj*) ; 

__attribute__((used)) static int vpif_s_std(struct file *file, void *priv, v4l2_std_id std_id)
{
	struct vpif_capture_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct vpif_capture_chan_config *chan_cfg;
	struct v4l2_input input;
	int ret;

	vpif_dbg(2, debug, "vpif_s_std\n");

	if (!config->chan_config[ch->channel_id].inputs)
		return -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inputs[ch->input_idx].input;
	if (input.capabilities != V4L2_IN_CAP_STD)
		return -ENODATA;

	if (vb2_is_busy(&common->buffer_queue))
		return -EBUSY;

	/* Call encoder subdevice function to set the standard */
	ch->video.stdid = std_id;
	memset(&ch->video.dv_timings, 0, sizeof(ch->video.dv_timings));

	/* Get the information about the standard */
	if (vpif_update_std_info(ch)) {
		vpif_err("Error getting the standard info\n");
		return -EINVAL;
	}

	/* set standard in the sub device */
	ret = v4l2_subdev_call(ch->sd, video, s_std, std_id);
	if (ret && ret != -ENOIOCTLCMD && ret != -ENODEV) {
		vpif_dbg(1, debug, "Failed to set standard for sub devices\n");
		return ret;
	}
	return 0;
}