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
struct intel_connector {TYPE_1__ panel; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

int intel_dsi_get_modes(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct drm_display_mode *mode;

	DRM_DEBUG_KMS("\n");

	if (!intel_connector->panel.fixed_mode) {
		DRM_DEBUG_KMS("no fixed mode\n");
		return 0;
	}

	mode = drm_mode_duplicate(connector->dev,
				  intel_connector->panel.fixed_mode);
	if (!mode) {
		DRM_DEBUG_KMS("drm_mode_duplicate failed\n");
		return 0;
	}

	drm_mode_probed_add(connector, mode);
	return 1;
}