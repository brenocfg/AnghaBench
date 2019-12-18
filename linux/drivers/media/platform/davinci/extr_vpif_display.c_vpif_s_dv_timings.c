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
struct vpif_channel_config_params {int l1; int vsize; int l5; int l7; int l11; int frm_fmt; int hd_sd; scalar_t__ stdid; scalar_t__ vbi_supported; scalar_t__ capture_format; scalar_t__ ycmux_mode; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  name; scalar_t__ l9; scalar_t__ l3; scalar_t__ sav2eav; scalar_t__ eav2sav; } ;
struct vpif_params {struct vpif_channel_config_params std_info; } ;
struct vpif_display_config {struct vpif_display_chan_config* chan_config; } ;
struct vpif_display_chan_config {TYPE_1__* outputs; } ;
struct v4l2_bt_timings {int vfrontporch; int il_vfrontporch; scalar_t__ interlaced; scalar_t__ height; scalar_t__ width; scalar_t__ il_vbackporch; scalar_t__ il_vsync; scalar_t__ vbackporch; scalar_t__ vsync; scalar_t__ hsync; scalar_t__ hfrontporch; scalar_t__ hbackporch; } ;
struct v4l2_dv_timings {scalar_t__ type; struct v4l2_bt_timings bt; } ;
struct video_obj {scalar_t__ stdid; struct v4l2_dv_timings dv_timings; } ;
struct video_device {int dummy; } ;
struct v4l2_output {scalar_t__ capabilities; } ;
struct file {int dummy; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; } ;
struct channel_obj {size_t channel_id; size_t output_idx; int /*<<< orphan*/  sd; struct video_obj video; struct common_obj* common; struct vpif_params vpifparams; } ;
struct TYPE_4__ {struct vpif_display_config* platform_data; } ;
struct TYPE_3__ {struct v4l2_output output; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 scalar_t__ V4L2_DV_BT_656_1120 ; 
 scalar_t__ V4L2_DV_BT_BLANKING_WIDTH (struct v4l2_bt_timings*) ; 
 int V4L2_DV_BT_FRAME_HEIGHT (struct v4l2_bt_timings*) ; 
 scalar_t__ V4L2_OUT_CAP_DV_TIMINGS ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  s_dv_timings ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dv_timings*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct video_device* video_devdata (struct file*) ; 
 struct channel_obj* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* vpif_dev ; 

__attribute__((used)) static int vpif_s_dv_timings(struct file *file, void *priv,
		struct v4l2_dv_timings *timings)
{
	struct vpif_display_config *config = vpif_dev->platform_data;
	struct video_device *vdev = video_devdata(file);
	struct channel_obj *ch = video_get_drvdata(vdev);
	struct vpif_params *vpifparams = &ch->vpifparams;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct vpif_channel_config_params *std_info = &vpifparams->std_info;
	struct video_obj *vid_ch = &ch->video;
	struct v4l2_bt_timings *bt = &vid_ch->dv_timings.bt;
	struct vpif_display_chan_config *chan_cfg;
	struct v4l2_output output;
	int ret;

	if (!config->chan_config[ch->channel_id].outputs)
		return -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outputs[ch->output_idx].output;
	if (output.capabilities != V4L2_OUT_CAP_DV_TIMINGS)
		return -ENODATA;

	if (vb2_is_busy(&common->buffer_queue))
		return -EBUSY;

	if (timings->type != V4L2_DV_BT_656_1120) {
		vpif_dbg(2, debug, "Timing type not defined\n");
		return -EINVAL;
	}

	/* Configure subdevice timings, if any */
	ret = v4l2_subdev_call(ch->sd, video, s_dv_timings, timings);
	if (ret == -ENOIOCTLCMD || ret == -ENODEV)
		ret = 0;
	if (ret < 0) {
		vpif_dbg(2, debug, "Error setting custom DV timings\n");
		return ret;
	}

	if (!(timings->bt.width && timings->bt.height &&
				(timings->bt.hbackporch ||
				 timings->bt.hfrontporch ||
				 timings->bt.hsync) &&
				timings->bt.vfrontporch &&
				(timings->bt.vbackporch ||
				 timings->bt.vsync))) {
		vpif_dbg(2, debug, "Timings for width, height, horizontal back porch, horizontal sync, horizontal front porch, vertical back porch, vertical sync and vertical back porch must be defined\n");
		return -EINVAL;
	}

	vid_ch->dv_timings = *timings;

	/* Configure video port timings */

	std_info->eav2sav = V4L2_DV_BT_BLANKING_WIDTH(bt) - 8;
	std_info->sav2eav = bt->width;

	std_info->l1 = 1;
	std_info->l3 = bt->vsync + bt->vbackporch + 1;

	std_info->vsize = V4L2_DV_BT_FRAME_HEIGHT(bt);
	if (bt->interlaced) {
		if (bt->il_vbackporch || bt->il_vfrontporch || bt->il_vsync) {
			std_info->l5 = std_info->vsize/2 -
				(bt->vfrontporch - 1);
			std_info->l7 = std_info->vsize/2 + 1;
			std_info->l9 = std_info->l7 + bt->il_vsync +
				bt->il_vbackporch + 1;
			std_info->l11 = std_info->vsize -
				(bt->il_vfrontporch - 1);
		} else {
			vpif_dbg(2, debug, "Required timing values for interlaced BT format missing\n");
			return -EINVAL;
		}
	} else {
		std_info->l5 = std_info->vsize - (bt->vfrontporch - 1);
	}
	strscpy(std_info->name, "Custom timings BT656/1120",
		sizeof(std_info->name));
	std_info->width = bt->width;
	std_info->height = bt->height;
	std_info->frm_fmt = bt->interlaced ? 0 : 1;
	std_info->ycmux_mode = 0;
	std_info->capture_format = 0;
	std_info->vbi_supported = 0;
	std_info->hd_sd = 1;
	std_info->stdid = 0;
	vid_ch->stdid = 0;

	return 0;
}