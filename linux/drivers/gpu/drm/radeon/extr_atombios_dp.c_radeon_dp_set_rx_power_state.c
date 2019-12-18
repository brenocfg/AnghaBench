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
struct radeon_connector_atom_dig {int* dpcd; } ;
struct radeon_connector {TYPE_1__* ddc_bus; struct radeon_connector_atom_dig* con_priv; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SET_POWER ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void radeon_dp_set_rx_power_state(struct drm_connector *connector,
				  u8 power_state)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector_atom_dig *dig_connector;

	if (!radeon_connector->con_priv)
		return;

	dig_connector = radeon_connector->con_priv;

	/* power up/down the sink */
	if (dig_connector->dpcd[0] >= 0x11) {
		drm_dp_dpcd_writeb(&radeon_connector->ddc_bus->aux,
				   DP_SET_POWER, power_state);
		usleep_range(1000, 2000);
	}
}