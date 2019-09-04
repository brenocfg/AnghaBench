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
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; int /*<<< orphan*/  probed_modes; } ;
struct TYPE_3__ {struct drm_display_mode* fixed_mode; } ;
struct TYPE_4__ {TYPE_1__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS_PIN_DPC ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  intel_ddc_get_modes (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int intel_dvo_get_modes(struct drm_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	const struct drm_display_mode *fixed_mode =
		to_intel_connector(connector)->panel.fixed_mode;

	/*
	 * We should probably have an i2c driver get_modes function for those
	 * devices which will have a fixed set of modes determined by the chip
	 * (TV-out, for example), but for now with just TMDS and LVDS,
	 * that's not the case.
	 */
	intel_ddc_get_modes(connector,
			    intel_gmbus_get_adapter(dev_priv, GMBUS_PIN_DPC));
	if (!list_empty(&connector->probed_modes))
		return 1;

	if (fixed_mode) {
		struct drm_display_mode *mode;
		mode = drm_mode_duplicate(connector->dev, fixed_mode);
		if (mode) {
			drm_mode_probed_add(connector, mode);
			return 1;
		}
	}

	return 0;
}