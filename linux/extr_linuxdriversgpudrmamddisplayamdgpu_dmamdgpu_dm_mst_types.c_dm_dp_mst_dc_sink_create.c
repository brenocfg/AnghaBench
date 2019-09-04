#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct drm_connector {int dummy; } ;
struct dc_sink_init_data {int /*<<< orphan*/  sink_signal; int /*<<< orphan*/  link; } ;
struct dc_sink {struct amdgpu_dm_connector* priv; } ;
struct amdgpu_dm_connector {TYPE_4__* edid; struct dc_sink* dc_sink; int /*<<< orphan*/  dc_link; TYPE_3__* port; } ;
struct TYPE_9__ {int extensions; } ;
struct TYPE_6__ {int /*<<< orphan*/  algo; } ;
struct TYPE_7__ {TYPE_1__ ddc; } ;
struct TYPE_8__ {TYPE_2__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_4__*) ; 
 int EDID_LENGTH ; 
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int /*<<< orphan*/  amdgpu_dm_add_sink_to_freesync_module (struct drm_connector*,TYPE_4__*) ; 
 struct dc_sink* dc_link_add_remote_sink (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct dc_sink_init_data*) ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (struct drm_connector*) ; 

void dm_dp_mst_dc_sink_create(struct drm_connector *connector)
{
	struct amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	struct dc_sink *dc_sink;
	struct dc_sink_init_data init_params = {
			.link = aconnector->dc_link,
			.sink_signal = SIGNAL_TYPE_DISPLAY_PORT_MST };

	/* FIXME none of this is safe. we shouldn't touch aconnector here in
	 * atomic_check
	 */

	/*
	 * TODO: Need to further figure out why ddc.algo is NULL while MST port exists
	 */
	if (!aconnector->port || !aconnector->port->aux.ddc.algo)
		return;

	ASSERT(aconnector->edid);

	dc_sink = dc_link_add_remote_sink(
		aconnector->dc_link,
		(uint8_t *)aconnector->edid,
		(aconnector->edid->extensions + 1) * EDID_LENGTH,
		&init_params);

	dc_sink->priv = aconnector;
	aconnector->dc_sink = dc_sink;

	amdgpu_dm_add_sink_to_freesync_module(
			connector, aconnector->edid);
}