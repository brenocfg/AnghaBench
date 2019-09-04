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
struct vpif_subdev_info {int /*<<< orphan*/  name; } ;
struct vpif_display_config {int subdev_count; struct vpif_subdev_info* subdevinfo; } ;
struct vpif_display_chan_config {TYPE_1__* outputs; } ;
struct TYPE_2__ {char* subdev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
vpif_output_to_subdev(struct vpif_display_config *vpif_cfg,
		      struct vpif_display_chan_config *chan_cfg, int index)
{
	struct vpif_subdev_info *subdev_info;
	const char *subdev_name;
	int i;

	vpif_dbg(2, debug, "vpif_output_to_subdev\n");

	if (!chan_cfg->outputs)
		return -1;

	subdev_name = chan_cfg->outputs[index].subdev_name;
	if (!subdev_name)
		return -1;

	/* loop through the sub device list to get the sub device info */
	for (i = 0; i < vpif_cfg->subdev_count; i++) {
		subdev_info = &vpif_cfg->subdevinfo[i];
		if (!strcmp(subdev_info->name, subdev_name))
			return i;
	}
	return -1;
}