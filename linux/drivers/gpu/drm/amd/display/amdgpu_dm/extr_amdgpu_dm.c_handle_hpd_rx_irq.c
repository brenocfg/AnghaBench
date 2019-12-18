#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int dummy; } ;
struct drm_connector {scalar_t__ force; struct drm_device* dev; } ;
struct TYPE_5__ {scalar_t__ lane_count; } ;
struct dc_link {scalar_t__ type; TYPE_2__ cur_link_settings; } ;
struct TYPE_6__ {int /*<<< orphan*/  aux; } ;
struct TYPE_4__ {int mst_state; } ;
struct amdgpu_dm_connector {int fake_enable; int /*<<< orphan*/  hpd_lock; TYPE_3__ dm_dp_aux; struct drm_connector base; TYPE_1__ mst_mgr; struct dc_link* dc_link; } ;
typedef  enum dc_connection_type { ____Placeholder_dc_connection_type } dc_connection_type ;

/* Variables and functions */
 int /*<<< orphan*/  DETECT_REASON_HPDRX ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 int /*<<< orphan*/  amdgpu_dm_update_connector_after_detect (struct amdgpu_dm_connector*) ; 
 scalar_t__ dc_connection_mst_branch ; 
 int dc_connection_none ; 
 scalar_t__ dc_link_detect (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_link_detect_sink (struct dc_link*,int*) ; 
 scalar_t__ dc_link_handle_hpd_rx_irq (struct dc_link*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_handle_hpd_rx_irq (struct amdgpu_dm_connector*) ; 
 int /*<<< orphan*/  dm_restore_drm_connector_state (struct drm_device*,struct drm_connector*) ; 
 int /*<<< orphan*/  drm_dp_cec_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  emulated_link_detect (struct dc_link*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_hpd_rx_irq(void *param)
{
	struct amdgpu_dm_connector *aconnector = (struct amdgpu_dm_connector *)param;
	struct drm_connector *connector = &aconnector->base;
	struct drm_device *dev = connector->dev;
	struct dc_link *dc_link = aconnector->dc_link;
	bool is_mst_root_connector = aconnector->mst_mgr.mst_state;
	enum dc_connection_type new_connection_type = dc_connection_none;

	/*
	 * TODO:Temporary add mutex to protect hpd interrupt not have a gpio
	 * conflict, after implement i2c helper, this mutex should be
	 * retired.
	 */
	if (dc_link->type != dc_connection_mst_branch)
		mutex_lock(&aconnector->hpd_lock);

	if (dc_link_handle_hpd_rx_irq(dc_link, NULL, NULL) &&
			!is_mst_root_connector) {
		/* Downstream Port status changed. */
		if (!dc_link_detect_sink(dc_link, &new_connection_type))
			DRM_ERROR("KMS: Failed to detect connector\n");

		if (aconnector->base.force && new_connection_type == dc_connection_none) {
			emulated_link_detect(dc_link);

			if (aconnector->fake_enable)
				aconnector->fake_enable = false;

			amdgpu_dm_update_connector_after_detect(aconnector);


			drm_modeset_lock_all(dev);
			dm_restore_drm_connector_state(dev, connector);
			drm_modeset_unlock_all(dev);

			drm_kms_helper_hotplug_event(dev);
		} else if (dc_link_detect(dc_link, DETECT_REASON_HPDRX)) {

			if (aconnector->fake_enable)
				aconnector->fake_enable = false;

			amdgpu_dm_update_connector_after_detect(aconnector);


			drm_modeset_lock_all(dev);
			dm_restore_drm_connector_state(dev, connector);
			drm_modeset_unlock_all(dev);

			drm_kms_helper_hotplug_event(dev);
		}
	}
	if ((dc_link->cur_link_settings.lane_count != LANE_COUNT_UNKNOWN) ||
	    (dc_link->type == dc_connection_mst_branch))
		dm_handle_hpd_rx_irq(aconnector);

	if (dc_link->type != dc_connection_mst_branch) {
		drm_dp_cec_irq(&aconnector->dm_dp_aux.aux);
		mutex_unlock(&aconnector->hpd_lock);
	}
}