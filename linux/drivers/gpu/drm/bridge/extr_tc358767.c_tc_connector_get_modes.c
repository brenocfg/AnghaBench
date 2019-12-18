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
struct TYPE_2__ {int /*<<< orphan*/  ddc; } ;
struct tc_data {struct edid* edid; TYPE_1__ aux; int /*<<< orphan*/  panel; int /*<<< orphan*/  dev; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct tc_data* connector_to_tc (struct drm_connector*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_panel_get_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int tc_get_display_props (struct tc_data*) ; 

__attribute__((used)) static int tc_connector_get_modes(struct drm_connector *connector)
{
	struct tc_data *tc = connector_to_tc(connector);
	struct edid *edid;
	int count;
	int ret;

	ret = tc_get_display_props(tc);
	if (ret < 0) {
		dev_err(tc->dev, "failed to read display props: %d\n", ret);
		return 0;
	}

	count = drm_panel_get_modes(tc->panel);
	if (count > 0)
		return count;

	edid = drm_get_edid(connector, &tc->aux.ddc);

	kfree(tc->edid);
	tc->edid = edid;
	if (!edid)
		return 0;

	drm_connector_update_edid_property(connector, edid);
	count = drm_add_edid_modes(connector, edid);

	return count;
}