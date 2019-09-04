#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vpif_subdev_info {int /*<<< orphan*/  name; } ;
struct vpif_capture_config {int (* setup_input_path ) (size_t,int /*<<< orphan*/ ) ;struct vpif_subdev_info* subdev_info; struct vpif_capture_chan_config* chan_config; } ;
struct vpif_capture_chan_config {TYPE_4__* inputs; int /*<<< orphan*/  vpif_if; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tvnorms; } ;
struct TYPE_6__ {int /*<<< orphan*/  iface; } ;
struct channel_obj {size_t channel_id; int input_idx; TYPE_2__ video_dev; TYPE_1__ vpifparams; struct v4l2_subdev* sd; } ;
struct TYPE_10__ {struct v4l2_subdev** sd; } ;
struct TYPE_8__ {int /*<<< orphan*/  std; } ;
struct TYPE_9__ {TYPE_3__ input; int /*<<< orphan*/  output_route; int /*<<< orphan*/  input_route; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  s_routing ; 
 int stub1 (size_t,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*,...) ; 
 int vpif_input_to_subdev (struct vpif_capture_config*,struct vpif_capture_chan_config*,int) ; 
 TYPE_5__ vpif_obj ; 

__attribute__((used)) static int vpif_set_input(
		struct vpif_capture_config *vpif_cfg,
		struct channel_obj *ch,
		int index)
{
	struct vpif_capture_chan_config *chan_cfg =
			&vpif_cfg->chan_config[ch->channel_id];
	struct vpif_subdev_info *subdev_info = NULL;
	struct v4l2_subdev *sd = NULL;
	u32 input = 0, output = 0;
	int sd_index;
	int ret;

	sd_index = vpif_input_to_subdev(vpif_cfg, chan_cfg, index);
	if (sd_index >= 0) {
		sd = vpif_obj.sd[sd_index];
		subdev_info = &vpif_cfg->subdev_info[sd_index];
	} else {
		/* no subdevice, no input to setup */
		return 0;
	}

	/* first setup input path from sub device to vpif */
	if (sd && vpif_cfg->setup_input_path) {
		ret = vpif_cfg->setup_input_path(ch->channel_id,
				       subdev_info->name);
		if (ret < 0) {
			vpif_dbg(1, debug, "couldn't setup input path for the" \
			" sub device %s, for input index %d\n",
			subdev_info->name, index);
			return ret;
		}
	}

	if (sd) {
		input = chan_cfg->inputs[index].input_route;
		output = chan_cfg->inputs[index].output_route;
		ret = v4l2_subdev_call(sd, video, s_routing,
				input, output, 0);
		if (ret < 0 && ret != -ENOIOCTLCMD) {
			vpif_dbg(1, debug, "Failed to set input\n");
			return ret;
		}
	}
	ch->input_idx = index;
	ch->sd = sd;
	/* copy interface parameters to vpif */
	ch->vpifparams.iface = chan_cfg->vpif_if;

	/* update tvnorms from the sub device input info */
	ch->video_dev.tvnorms = chan_cfg->inputs[index].input.std;
	return 0;
}