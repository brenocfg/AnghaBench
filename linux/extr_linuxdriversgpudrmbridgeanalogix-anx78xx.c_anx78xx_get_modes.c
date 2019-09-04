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
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddc; } ;
struct anx78xx {int /*<<< orphan*/  lock; scalar_t__ edid; TYPE_1__ aux; int /*<<< orphan*/  powered; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ WARN_ON (int) ; 
 int anx78xx_get_downstream_info (struct anx78xx*) ; 
 struct anx78xx* connector_to_anx78xx (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,scalar_t__) ; 
 int drm_connector_update_edid_property (struct drm_connector*,scalar_t__) ; 
 scalar_t__ drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int anx78xx_get_modes(struct drm_connector *connector)
{
	struct anx78xx *anx78xx = connector_to_anx78xx(connector);
	int err, num_modes = 0;

	if (WARN_ON(!anx78xx->powered))
		return 0;

	if (anx78xx->edid)
		return drm_add_edid_modes(connector, anx78xx->edid);

	mutex_lock(&anx78xx->lock);

	err = anx78xx_get_downstream_info(anx78xx);
	if (err) {
		DRM_ERROR("Failed to get downstream info: %d\n", err);
		goto unlock;
	}

	anx78xx->edid = drm_get_edid(connector, &anx78xx->aux.ddc);
	if (!anx78xx->edid) {
		DRM_ERROR("Failed to read EDID\n");
		goto unlock;
	}

	err = drm_connector_update_edid_property(connector,
						 anx78xx->edid);
	if (err) {
		DRM_ERROR("Failed to update EDID property: %d\n", err);
		goto unlock;
	}

	num_modes = drm_add_edid_modes(connector, anx78xx->edid);

unlock:
	mutex_unlock(&anx78xx->lock);

	return num_modes;
}