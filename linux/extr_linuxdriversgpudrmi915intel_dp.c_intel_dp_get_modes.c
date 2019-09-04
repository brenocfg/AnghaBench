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
struct TYPE_2__ {scalar_t__ fixed_mode; } ;
struct intel_connector {TYPE_1__ panel; struct edid* detect_edid; } ;
struct edid {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_attached_dp (struct drm_connector*) ; 
 int intel_connector_update_modes (struct drm_connector*,struct edid*) ; 
 scalar_t__ intel_dp_is_edp (int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int intel_dp_get_modes(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct edid *edid;

	edid = intel_connector->detect_edid;
	if (edid) {
		int ret = intel_connector_update_modes(connector, edid);
		if (ret)
			return ret;
	}

	/* if eDP has no EDID, fall back to fixed mode */
	if (intel_dp_is_edp(intel_attached_dp(connector)) &&
	    intel_connector->panel.fixed_mode) {
		struct drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev,
					  intel_connector->panel.fixed_mode);
		if (mode) {
			drm_mode_probed_add(connector, mode);
			return 1;
		}
	}

	return 0;
}