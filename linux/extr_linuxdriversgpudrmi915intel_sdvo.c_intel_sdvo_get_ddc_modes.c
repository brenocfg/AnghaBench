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
struct edid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 scalar_t__ intel_sdvo_connector_matches_edid (int /*<<< orphan*/ ,struct edid*) ; 
 struct edid* intel_sdvo_get_analog_edid (struct drm_connector*) ; 
 struct edid* intel_sdvo_get_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int /*<<< orphan*/  to_intel_sdvo_connector (struct drm_connector*) ; 

__attribute__((used)) static void intel_sdvo_get_ddc_modes(struct drm_connector *connector)
{
	struct edid *edid;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	/* set the bus switch and get the modes */
	edid = intel_sdvo_get_edid(connector);

	/*
	 * Mac mini hack.  On this device, the DVI-I connector shares one DDC
	 * link between analog and digital outputs. So, if the regular SDVO
	 * DDC fails, check to see if the analog output is disconnected, in
	 * which case we'll look there for the digital DDC data.
	 */
	if (edid == NULL)
		edid = intel_sdvo_get_analog_edid(connector);

	if (edid != NULL) {
		if (intel_sdvo_connector_matches_edid(to_intel_sdvo_connector(connector),
						      edid)) {
			drm_connector_update_edid_property(connector, edid);
			drm_add_edid_modes(connector, edid);
		}

		kfree(edid);
	}
}