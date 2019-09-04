#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vpif_display_config {struct vpif_display_chan_config* chan_config; } ;
struct vpif_display_chan_config {TYPE_3__* outputs; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tvnorms; } ;
struct channel_obj {size_t channel_id; int output_idx; TYPE_1__ video_dev; struct v4l2_subdev* sd; } ;
struct TYPE_8__ {struct v4l2_subdev** sd; } ;
struct TYPE_6__ {int /*<<< orphan*/  std; } ;
struct TYPE_7__ {TYPE_2__ output; int /*<<< orphan*/  output_route; int /*<<< orphan*/  input_route; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  s_routing ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  vpif_err (char*) ; 
 TYPE_4__ vpif_obj ; 
 int vpif_output_to_subdev (struct vpif_display_config*,struct vpif_display_chan_config*,int) ; 

__attribute__((used)) static int vpif_set_output(struct vpif_display_config *vpif_cfg,
		      struct channel_obj *ch, int index)
{
	struct vpif_display_chan_config *chan_cfg =
		&vpif_cfg->chan_config[ch->channel_id];
	struct v4l2_subdev *sd = NULL;
	u32 input = 0, output = 0;
	int sd_index;
	int ret;

	sd_index = vpif_output_to_subdev(vpif_cfg, chan_cfg, index);
	if (sd_index >= 0)
		sd = vpif_obj.sd[sd_index];

	if (sd) {
		input = chan_cfg->outputs[index].input_route;
		output = chan_cfg->outputs[index].output_route;
		ret = v4l2_subdev_call(sd, video, s_routing, input, output, 0);
		if (ret < 0 && ret != -ENOIOCTLCMD) {
			vpif_err("Failed to set output\n");
			return ret;
		}

	}
	ch->output_idx = index;
	ch->sd = sd;
	if (chan_cfg->outputs)
		/* update tvnorms from the sub device output info */
		ch->video_dev.tvnorms = chan_cfg->outputs[index].output.std;
	return 0;
}