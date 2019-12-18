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
typedef  int /*<<< orphan*/  uint8_t ;
struct edid {int extensions; } ;
struct dc_sink_init_data {int /*<<< orphan*/  sink_signal; TYPE_3__* link; } ;
struct TYPE_5__ {scalar_t__ force; int override_edid; TYPE_1__* edid_blob_ptr; int /*<<< orphan*/  name; } ;
struct amdgpu_dm_connector {scalar_t__ dc_sink; scalar_t__ dc_em_sink; TYPE_3__* dc_link; TYPE_2__ base; struct edid* edid; } ;
struct TYPE_6__ {scalar_t__ local_sink; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_FORCE_OFF ; 
 scalar_t__ DRM_FORCE_ON ; 
 int EDID_LENGTH ; 
 int /*<<< orphan*/  SIGNAL_TYPE_VIRTUAL ; 
 scalar_t__ dc_link_add_remote_sink (TYPE_3__*,int /*<<< orphan*/ *,int,struct dc_sink_init_data*) ; 
 int /*<<< orphan*/  dc_sink_retain (scalar_t__) ; 

__attribute__((used)) static void create_eml_sink(struct amdgpu_dm_connector *aconnector)
{
	struct dc_sink_init_data init_params = {
			.link = aconnector->dc_link,
			.sink_signal = SIGNAL_TYPE_VIRTUAL
	};
	struct edid *edid;

	if (!aconnector->base.edid_blob_ptr) {
		DRM_ERROR("No EDID firmware found on connector: %s ,forcing to OFF!\n",
				aconnector->base.name);

		aconnector->base.force = DRM_FORCE_OFF;
		aconnector->base.override_edid = false;
		return;
	}

	edid = (struct edid *) aconnector->base.edid_blob_ptr->data;

	aconnector->edid = edid;

	aconnector->dc_em_sink = dc_link_add_remote_sink(
		aconnector->dc_link,
		(uint8_t *)edid,
		(edid->extensions + 1) * EDID_LENGTH,
		&init_params);

	if (aconnector->base.force == DRM_FORCE_ON) {
		aconnector->dc_sink = aconnector->dc_link->local_sink ?
		aconnector->dc_link->local_sink :
		aconnector->dc_em_sink;
		dc_sink_retain(aconnector->dc_sink);
	}
}