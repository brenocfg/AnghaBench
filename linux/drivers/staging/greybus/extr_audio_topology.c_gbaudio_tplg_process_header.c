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
struct gbaudio_module_info {unsigned long dai_offset; unsigned long control_offset; unsigned long widget_offset; unsigned long route_offset; int /*<<< orphan*/  dev; int /*<<< orphan*/  num_dapm_routes; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  num_controls; } ;
struct gb_audio_topology {int /*<<< orphan*/  size_widgets; int /*<<< orphan*/  size_controls; int /*<<< orphan*/  size_dais; int /*<<< orphan*/  data; int /*<<< orphan*/  num_routes; int /*<<< orphan*/  num_widgets; int /*<<< orphan*/  num_controls; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbaudio_tplg_process_header(struct gbaudio_module_info *module,
				       struct gb_audio_topology *tplg_data)
{
	/* fetch no. of kcontrols, widgets & routes */
	module->num_controls = tplg_data->num_controls;
	module->num_dapm_widgets = tplg_data->num_widgets;
	module->num_dapm_routes = tplg_data->num_routes;

	/* update block offset */
	module->dai_offset = (unsigned long)&tplg_data->data;
	module->control_offset = module->dai_offset +
					le32_to_cpu(tplg_data->size_dais);
	module->widget_offset = module->control_offset +
					le32_to_cpu(tplg_data->size_controls);
	module->route_offset = module->widget_offset +
					le32_to_cpu(tplg_data->size_widgets);

	dev_dbg(module->dev, "DAI offset is 0x%lx\n", module->dai_offset);
	dev_dbg(module->dev, "control offset is %lx\n",
		module->control_offset);
	dev_dbg(module->dev, "widget offset is %lx\n", module->widget_offset);
	dev_dbg(module->dev, "route offset is %lx\n", module->route_offset);

	return 0;
}