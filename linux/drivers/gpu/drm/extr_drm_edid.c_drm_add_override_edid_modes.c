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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_override_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

int drm_add_override_edid_modes(struct drm_connector *connector)
{
	struct edid *override;
	int num_modes = 0;

	override = drm_get_override_edid(connector);
	if (override) {
		drm_connector_update_edid_property(connector, override);
		num_modes = drm_add_edid_modes(connector, override);
		kfree(override);

		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] adding %d modes via fallback override/firmware EDID\n",
			      connector->base.id, connector->name, num_modes);
	}

	return num_modes;
}