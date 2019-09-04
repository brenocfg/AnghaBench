#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct edid {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_4__ mode_config; } ;
struct drm_connector {scalar_t__ force; struct drm_device* dev; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ raw_edid; } ;
struct dc_sink {scalar_t__ sink_signal; TYPE_3__ dc_edid; } ;
struct TYPE_5__ {int mst_state; } ;
struct amdgpu_dm_connector {struct edid* edid; struct dc_sink* dc_sink; scalar_t__ num_modes; int /*<<< orphan*/  connector_id; struct dc_sink* dc_em_sink; struct drm_connector base; TYPE_2__* dc_link; TYPE_1__ mst_mgr; } ;
struct TYPE_6__ {struct dc_sink* local_sink; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ DRM_FORCE_UNSPECIFIED ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int /*<<< orphan*/  amdgpu_dm_add_sink_to_freesync_module (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  amdgpu_dm_remove_sink_from_freesync_module (struct drm_connector*) ; 
 int /*<<< orphan*/  dc_sink_release (struct dc_sink*) ; 
 int /*<<< orphan*/  dc_sink_retain (struct dc_sink*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
amdgpu_dm_update_connector_after_detect(struct amdgpu_dm_connector *aconnector)
{
	struct drm_connector *connector = &aconnector->base;
	struct drm_device *dev = connector->dev;
	struct dc_sink *sink;

	/* MST handled by drm_mst framework */
	if (aconnector->mst_mgr.mst_state == true)
		return;


	sink = aconnector->dc_link->local_sink;

	/* Edid mgmt connector gets first update only in mode_valid hook and then
	 * the connector sink is set to either fake or physical sink depends on link status.
	 * don't do it here if u are during boot
	 */
	if (aconnector->base.force != DRM_FORCE_UNSPECIFIED
			&& aconnector->dc_em_sink) {

		/* For S3 resume with headless use eml_sink to fake stream
		 * because on resume connecotr->sink is set ti NULL
		 */
		mutex_lock(&dev->mode_config.mutex);

		if (sink) {
			if (aconnector->dc_sink) {
				amdgpu_dm_remove_sink_from_freesync_module(
								connector);
				/* retain and release bellow are used for
				 * bump up refcount for sink because the link don't point
				 * to it anymore after disconnect so on next crtc to connector
				 * reshuffle by UMD we will get into unwanted dc_sink release
				 */
				if (aconnector->dc_sink != aconnector->dc_em_sink)
					dc_sink_release(aconnector->dc_sink);
			}
			aconnector->dc_sink = sink;
			amdgpu_dm_add_sink_to_freesync_module(
						connector, aconnector->edid);
		} else {
			amdgpu_dm_remove_sink_from_freesync_module(connector);
			if (!aconnector->dc_sink)
				aconnector->dc_sink = aconnector->dc_em_sink;
			else if (aconnector->dc_sink != aconnector->dc_em_sink)
				dc_sink_retain(aconnector->dc_sink);
		}

		mutex_unlock(&dev->mode_config.mutex);
		return;
	}

	/*
	 * TODO: temporary guard to look for proper fix
	 * if this sink is MST sink, we should not do anything
	 */
	if (sink && sink->sink_signal == SIGNAL_TYPE_DISPLAY_PORT_MST)
		return;

	if (aconnector->dc_sink == sink) {
		/* We got a DP short pulse (Link Loss, DP CTS, etc...).
		 * Do nothing!! */
		DRM_DEBUG_DRIVER("DCHPD: connector_id=%d: dc_sink didn't change.\n",
				aconnector->connector_id);
		return;
	}

	DRM_DEBUG_DRIVER("DCHPD: connector_id=%d: Old sink=%p New sink=%p\n",
		aconnector->connector_id, aconnector->dc_sink, sink);

	mutex_lock(&dev->mode_config.mutex);

	/* 1. Update status of the drm connector
	 * 2. Send an event and let userspace tell us what to do */
	if (sink) {
		/* TODO: check if we still need the S3 mode update workaround.
		 * If yes, put it here. */
		if (aconnector->dc_sink)
			amdgpu_dm_remove_sink_from_freesync_module(
							connector);

		aconnector->dc_sink = sink;
		if (sink->dc_edid.length == 0) {
			aconnector->edid = NULL;
		} else {
			aconnector->edid =
				(struct edid *) sink->dc_edid.raw_edid;


			drm_connector_update_edid_property(connector,
					aconnector->edid);
		}
		amdgpu_dm_add_sink_to_freesync_module(connector, aconnector->edid);

	} else {
		amdgpu_dm_remove_sink_from_freesync_module(connector);
		drm_connector_update_edid_property(connector, NULL);
		aconnector->num_modes = 0;
		aconnector->dc_sink = NULL;
		aconnector->edid = NULL;
	}

	mutex_unlock(&dev->mode_config.mutex);
}