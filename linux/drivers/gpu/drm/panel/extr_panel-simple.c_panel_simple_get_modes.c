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
struct panel_simple {scalar_t__ ddc; } ;
struct edid {int dummy; } ;
struct drm_panel {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 scalar_t__ drm_add_edid_modes (int /*<<< orphan*/ ,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (int /*<<< orphan*/ ,struct edid*) ; 
 struct edid* drm_get_edid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 scalar_t__ panel_simple_get_non_edid_modes (struct panel_simple*) ; 
 struct panel_simple* to_panel_simple (struct drm_panel*) ; 

__attribute__((used)) static int panel_simple_get_modes(struct drm_panel *panel)
{
	struct panel_simple *p = to_panel_simple(panel);
	int num = 0;

	/* probe EDID if a DDC bus is available */
	if (p->ddc) {
		struct edid *edid = drm_get_edid(panel->connector, p->ddc);
		drm_connector_update_edid_property(panel->connector, edid);
		if (edid) {
			num += drm_add_edid_modes(panel->connector, edid);
			kfree(edid);
		}
	}

	/* add hard-coded panel modes */
	num += panel_simple_get_non_edid_modes(p);

	return num;
}