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
struct drm_device {int dummy; } ;
struct drm_connector {scalar_t__ force; struct drm_device* dev; } ;
struct amdgpu_dm_connector {int fake_enable; int /*<<< orphan*/  hpd_lock; struct drm_connector base; int /*<<< orphan*/  dc_link; } ;
typedef  enum dc_connection_type { ____Placeholder_dc_connection_type } dc_connection_type ;

/* Variables and functions */
 int /*<<< orphan*/  DETECT_REASON_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ DRM_FORCE_UNSPECIFIED ; 
 int /*<<< orphan*/  amdgpu_dm_update_connector_after_detect (struct amdgpu_dm_connector*) ; 
 int dc_connection_none ; 
 scalar_t__ dc_link_detect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_link_detect_sink (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dm_restore_drm_connector_state (struct drm_device*,struct drm_connector*) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  emulated_link_detect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_hpd_irq(void *param)
{
	struct amdgpu_dm_connector *aconnector = (struct amdgpu_dm_connector *)param;
	struct drm_connector *connector = &aconnector->base;
	struct drm_device *dev = connector->dev;
	enum dc_connection_type new_connection_type = dc_connection_none;

	/*
	 * In case of failure or MST no need to update connector status or notify the OS
	 * since (for MST case) MST does this in its own context.
	 */
	mutex_lock(&aconnector->hpd_lock);

	if (aconnector->fake_enable)
		aconnector->fake_enable = false;

	if (!dc_link_detect_sink(aconnector->dc_link, &new_connection_type))
		DRM_ERROR("KMS: Failed to detect connector\n");

	if (aconnector->base.force && new_connection_type == dc_connection_none) {
		emulated_link_detect(aconnector->dc_link);


		drm_modeset_lock_all(dev);
		dm_restore_drm_connector_state(dev, connector);
		drm_modeset_unlock_all(dev);

		if (aconnector->base.force == DRM_FORCE_UNSPECIFIED)
			drm_kms_helper_hotplug_event(dev);

	} else if (dc_link_detect(aconnector->dc_link, DETECT_REASON_HPD)) {
		amdgpu_dm_update_connector_after_detect(aconnector);


		drm_modeset_lock_all(dev);
		dm_restore_drm_connector_state(dev, connector);
		drm_modeset_unlock_all(dev);

		if (aconnector->base.force == DRM_FORCE_UNSPECIFIED)
			drm_kms_helper_hotplug_event(dev);
	}
	mutex_unlock(&aconnector->hpd_lock);

}