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
struct tegra_output {int /*<<< orphan*/  cec; scalar_t__ ddc; scalar_t__ edid; TYPE_2__* panel; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* get_modes ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr_from_edid (int /*<<< orphan*/ ,struct edid*) ; 
 struct tegra_output* connector_to_output (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct edid* kmemdup (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 

int tegra_output_connector_get_modes(struct drm_connector *connector)
{
	struct tegra_output *output = connector_to_output(connector);
	struct edid *edid = NULL;
	int err = 0;

	/*
	 * If the panel provides one or more modes, use them exclusively and
	 * ignore any other means of obtaining a mode.
	 */
	if (output->panel) {
		err = output->panel->funcs->get_modes(output->panel);
		if (err > 0)
			return err;
	}

	if (output->edid)
		edid = kmemdup(output->edid, sizeof(*edid), GFP_KERNEL);
	else if (output->ddc)
		edid = drm_get_edid(connector, output->ddc);

	cec_notifier_set_phys_addr_from_edid(output->cec, edid);
	drm_connector_update_edid_property(connector, edid);

	if (edid) {
		err = drm_add_edid_modes(connector, edid);
		kfree(edid);
	}

	return err;
}