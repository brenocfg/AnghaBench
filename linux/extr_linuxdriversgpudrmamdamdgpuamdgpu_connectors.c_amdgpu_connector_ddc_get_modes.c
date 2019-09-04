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
struct drm_connector {int dummy; } ;
struct amdgpu_connector {int /*<<< orphan*/ * edid; } ;

/* Variables and functions */
 int drm_add_edid_modes (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 

__attribute__((used)) static int amdgpu_connector_ddc_get_modes(struct drm_connector *connector)
{
	struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	int ret;

	if (amdgpu_connector->edid) {
		drm_connector_update_edid_property(connector, amdgpu_connector->edid);
		ret = drm_add_edid_modes(connector, amdgpu_connector->edid);
		return ret;
	}
	drm_connector_update_edid_property(connector, NULL);
	return 0;
}