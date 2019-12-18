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
struct gbaudio_module_info {unsigned int jack_mask; unsigned int button_mask; int /*<<< orphan*/  dev; scalar_t__ route_offset; scalar_t__ widget_offset; scalar_t__ control_offset; } ;
struct gb_audio_widget {int dummy; } ;
struct gb_audio_topology {int /*<<< orphan*/  jack_type; } ;
struct gb_audio_route {int dummy; } ;
struct gb_audio_control {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GBCODEC_JACK_BUTTON_MASK ; 
 unsigned int GBCODEC_JACK_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gbaudio_tplg_process_header (struct gbaudio_module_info*,struct gb_audio_topology*) ; 
 int gbaudio_tplg_process_kcontrols (struct gbaudio_module_info*,struct gb_audio_control*) ; 
 int gbaudio_tplg_process_routes (struct gbaudio_module_info*,struct gb_audio_route*) ; 
 int gbaudio_tplg_process_widgets (struct gbaudio_module_info*,struct gb_audio_widget*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

int gbaudio_tplg_parse_data(struct gbaudio_module_info *module,
			    struct gb_audio_topology *tplg_data)
{
	int ret;
	struct gb_audio_control *controls;
	struct gb_audio_widget *widgets;
	struct gb_audio_route *routes;
	unsigned int jack_type;

	if (!tplg_data)
		return -EINVAL;

	ret = gbaudio_tplg_process_header(module, tplg_data);
	if (ret) {
		dev_err(module->dev, "%d: Error in parsing topology header\n",
			ret);
		return ret;
	}

	/* process control */
	controls = (struct gb_audio_control *)module->control_offset;
	ret = gbaudio_tplg_process_kcontrols(module, controls);
	if (ret) {
		dev_err(module->dev,
			"%d: Error in parsing controls data\n", ret);
		return ret;
	}
	dev_dbg(module->dev, "Control parsing finished\n");

	/* process widgets */
	widgets = (struct gb_audio_widget *)module->widget_offset;
	ret = gbaudio_tplg_process_widgets(module, widgets);
	if (ret) {
		dev_err(module->dev,
			"%d: Error in parsing widgets data\n", ret);
		return ret;
	}
	dev_dbg(module->dev, "Widget parsing finished\n");

	/* process route */
	routes = (struct gb_audio_route *)module->route_offset;
	ret = gbaudio_tplg_process_routes(module, routes);
	if (ret) {
		dev_err(module->dev,
			"%d: Error in parsing routes data\n", ret);
		return ret;
	}
	dev_dbg(module->dev, "Route parsing finished\n");

	/* parse jack capabilities */
	jack_type = le32_to_cpu(tplg_data->jack_type);
	if (jack_type) {
		module->jack_mask = jack_type & GBCODEC_JACK_MASK;
		module->button_mask = jack_type & GBCODEC_JACK_BUTTON_MASK;
	}

	return ret;
}