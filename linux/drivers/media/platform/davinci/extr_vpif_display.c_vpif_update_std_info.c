#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vpif_channel_config_params {scalar_t__ hd_sd; int stdid; } ;
struct vpif_params {struct vpif_channel_config_params std_info; } ;
struct video_obj {int stdid; } ;
struct channel_obj {struct vpif_params vpifparams; struct video_obj video; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memcpy (struct vpif_channel_config_params*,struct vpif_channel_config_params const*,int) ; 
 struct vpif_channel_config_params* vpif_ch_params ; 
 int vpif_ch_params_count ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_update_std_info(struct channel_obj *ch)
{
	struct video_obj *vid_ch = &ch->video;
	struct vpif_params *vpifparams = &ch->vpifparams;
	struct vpif_channel_config_params *std_info = &vpifparams->std_info;
	const struct vpif_channel_config_params *config;

	int i;

	for (i = 0; i < vpif_ch_params_count; i++) {
		config = &vpif_ch_params[i];
		if (config->hd_sd == 0) {
			vpif_dbg(2, debug, "SD format\n");
			if (config->stdid & vid_ch->stdid) {
				memcpy(std_info, config, sizeof(*config));
				break;
			}
		}
	}

	if (i == vpif_ch_params_count) {
		vpif_dbg(1, debug, "Format not found\n");
		return -EINVAL;
	}

	return 0;
}