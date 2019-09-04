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
struct radeon_connector {int /*<<< orphan*/ * edid; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int drm_add_edid_modes (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static int radeon_ddc_get_modes(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	int ret;

	if (radeon_connector->edid) {
		drm_connector_update_edid_property(connector, radeon_connector->edid);
		ret = drm_add_edid_modes(connector, radeon_connector->edid);
		return ret;
	}
	drm_connector_update_edid_property(connector, NULL);
	return 0;
}