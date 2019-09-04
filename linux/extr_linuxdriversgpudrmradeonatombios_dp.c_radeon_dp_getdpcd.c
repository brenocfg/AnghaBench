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
struct radeon_connector_atom_dig {scalar_t__* dpcd; } ;
struct radeon_connector {TYPE_1__* ddc_bus; struct radeon_connector_atom_dig* con_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int DP_DPCD_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,scalar_t__*) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_dp_probe_oui (struct radeon_connector*) ; 

bool radeon_dp_getdpcd(struct radeon_connector *radeon_connector)
{
	struct radeon_connector_atom_dig *dig_connector = radeon_connector->con_priv;
	u8 msg[DP_DPCD_SIZE];
	int ret;

	ret = drm_dp_dpcd_read(&radeon_connector->ddc_bus->aux, DP_DPCD_REV, msg,
			       DP_DPCD_SIZE);
	if (ret == DP_DPCD_SIZE) {
		memcpy(dig_connector->dpcd, msg, DP_DPCD_SIZE);

		DRM_DEBUG_KMS("DPCD: %*ph\n", (int)sizeof(dig_connector->dpcd),
			      dig_connector->dpcd);

		radeon_dp_probe_oui(radeon_connector);

		return true;
	}

	dig_connector->dpcd[0] = 0;
	return false;
}