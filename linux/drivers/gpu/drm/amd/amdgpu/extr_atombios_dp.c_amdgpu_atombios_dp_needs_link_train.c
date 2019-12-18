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
typedef  int /*<<< orphan*/  u8 ;
struct amdgpu_connector_atom_dig {int /*<<< orphan*/  dp_lane_count; } ;
struct amdgpu_connector {TYPE_1__* ddc_bus; struct amdgpu_connector_atom_dig* con_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int DP_LINK_STATUS_SIZE ; 
 scalar_t__ drm_dp_channel_eq_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_dpcd_read_link_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool amdgpu_atombios_dp_needs_link_train(struct amdgpu_connector *amdgpu_connector)
{
	u8 link_status[DP_LINK_STATUS_SIZE];
	struct amdgpu_connector_atom_dig *dig = amdgpu_connector->con_priv;

	if (drm_dp_dpcd_read_link_status(&amdgpu_connector->ddc_bus->aux, link_status)
	    <= 0)
		return false;
	if (drm_dp_channel_eq_ok(link_status, dig->dp_lane_count))
		return false;
	return true;
}