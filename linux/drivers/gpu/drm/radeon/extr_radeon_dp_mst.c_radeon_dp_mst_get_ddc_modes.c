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
struct radeon_connector {int /*<<< orphan*/  base; struct edid* edid; int /*<<< orphan*/  port; int /*<<< orphan*/  mst_mgr; struct radeon_connector* mst_port; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,struct edid*) ; 
 int drm_add_edid_modes (int /*<<< orphan*/ *,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (int /*<<< orphan*/ *,struct edid*) ; 
 struct edid* drm_dp_mst_get_edid (struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static int radeon_dp_mst_get_ddc_modes(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector *master = radeon_connector->mst_port;
	struct edid *edid;
	int ret = 0;

	edid = drm_dp_mst_get_edid(connector, &master->mst_mgr, radeon_connector->port);
	radeon_connector->edid = edid;
	DRM_DEBUG_KMS("edid retrieved %p\n", edid);
	if (radeon_connector->edid) {
		drm_connector_update_edid_property(&radeon_connector->base, radeon_connector->edid);
		ret = drm_add_edid_modes(&radeon_connector->base, radeon_connector->edid);
		return ret;
	}
	drm_connector_update_edid_property(&radeon_connector->base, NULL);

	return ret;
}