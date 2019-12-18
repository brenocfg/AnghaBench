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
struct TYPE_2__ {int /*<<< orphan*/  fixed_mode; } ;
struct intel_connector {TYPE_1__ panel; int /*<<< orphan*/  edid; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int drm_add_edid_modes (struct drm_connector*,int /*<<< orphan*/ ) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int intel_lvds_get_modes(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct drm_device *dev = connector->dev;
	struct drm_display_mode *mode;

	/* use cached edid if we have one */
	if (!IS_ERR_OR_NULL(intel_connector->edid))
		return drm_add_edid_modes(connector, intel_connector->edid);

	mode = drm_mode_duplicate(dev, intel_connector->panel.fixed_mode);
	if (mode == NULL)
		return 0;

	drm_mode_probed_add(connector, mode);
	return 1;
}