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
struct radeon_connector_atom_dig {int /*<<< orphan*/  dpcd; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;
struct drm_display_mode {int clock; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int MODE_CLOCK_HIGH ; 
 int MODE_OK ; 
 int /*<<< orphan*/  radeon_connector_is_dp12_capable (struct drm_connector*) ; 
 int radeon_dp_get_dp_link_config (struct drm_connector*,int /*<<< orphan*/ ,int,unsigned int*,unsigned int*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

int radeon_dp_mode_valid_helper(struct drm_connector *connector,
				struct drm_display_mode *mode)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector_atom_dig *dig_connector;
	unsigned dp_clock, dp_lanes;
	int ret;

	if ((mode->clock > 340000) &&
	    (!radeon_connector_is_dp12_capable(connector)))
		return MODE_CLOCK_HIGH;

	if (!radeon_connector->con_priv)
		return MODE_CLOCK_HIGH;
	dig_connector = radeon_connector->con_priv;

	ret = radeon_dp_get_dp_link_config(connector, dig_connector->dpcd,
					   mode->clock,
					   &dp_lanes,
					   &dp_clock);
	if (ret)
		return MODE_CLOCK_HIGH;

	if ((dp_clock == 540000) &&
	    (!radeon_connector_is_dp12_capable(connector)))
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}