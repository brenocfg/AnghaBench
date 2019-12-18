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
typedef  int /*<<< orphan*/  uint8_t ;
struct edid {int extensions; } ;
struct drm_connector {int dummy; } ;
struct dc_sink_init_data {int /*<<< orphan*/  sink_signal; int /*<<< orphan*/  link; } ;
struct dc_sink {scalar_t__ sink_signal; struct amdgpu_dm_connector* priv; } ;
struct amdgpu_dm_connector {struct edid* edid; int /*<<< orphan*/  base; struct dc_sink* dc_sink; int /*<<< orphan*/  dc_link; int /*<<< orphan*/  port; TYPE_1__* mst_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  mst_mgr; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ SIGNAL_TYPE_VIRTUAL ; 
 int /*<<< orphan*/  amdgpu_dm_update_freesync_caps (struct drm_connector*,struct edid*) ; 
 struct dc_sink* dc_link_add_remote_sink (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct dc_sink_init_data*) ; 
 int /*<<< orphan*/  dc_sink_release (struct dc_sink*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (int /*<<< orphan*/ *,struct edid*) ; 
 struct edid* drm_dp_mst_get_edid (struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (struct drm_connector*) ; 

__attribute__((used)) static int dm_dp_mst_get_modes(struct drm_connector *connector)
{
	struct amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	int ret = 0;

	if (!aconnector)
		return drm_add_edid_modes(connector, NULL);

	if (!aconnector->edid) {
		struct edid *edid;
		edid = drm_dp_mst_get_edid(connector, &aconnector->mst_port->mst_mgr, aconnector->port);

		if (!edid) {
			drm_connector_update_edid_property(
				&aconnector->base,
				NULL);
			return ret;
		}

		aconnector->edid = edid;
	}

	if (aconnector->dc_sink && aconnector->dc_sink->sink_signal == SIGNAL_TYPE_VIRTUAL) {
		dc_sink_release(aconnector->dc_sink);
		aconnector->dc_sink = NULL;
	}

	if (!aconnector->dc_sink) {
		struct dc_sink *dc_sink;
		struct dc_sink_init_data init_params = {
				.link = aconnector->dc_link,
				.sink_signal = SIGNAL_TYPE_DISPLAY_PORT_MST };
		dc_sink = dc_link_add_remote_sink(
			aconnector->dc_link,
			(uint8_t *)aconnector->edid,
			(aconnector->edid->extensions + 1) * EDID_LENGTH,
			&init_params);

		dc_sink->priv = aconnector;
		/* dc_link_add_remote_sink returns a new reference */
		aconnector->dc_sink = dc_sink;

		if (aconnector->dc_sink)
			amdgpu_dm_update_freesync_caps(
					connector, aconnector->edid);

	}

	drm_connector_update_edid_property(
					&aconnector->base, aconnector->edid);

	ret = drm_add_edid_modes(connector, aconnector->edid);

	return ret;
}