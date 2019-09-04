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
struct edid {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  probed_modes; } ;
struct amdgpu_dm_connector {scalar_t__ num_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_dm_get_native_mode (struct drm_connector*) ; 
 scalar_t__ drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (struct drm_connector*) ; 

__attribute__((used)) static void amdgpu_dm_connector_ddc_get_modes(struct drm_connector *connector,
					      struct edid *edid)
{
	struct amdgpu_dm_connector *amdgpu_dm_connector =
			to_amdgpu_dm_connector(connector);

	if (edid) {
		/* empty probed_modes */
		INIT_LIST_HEAD(&connector->probed_modes);
		amdgpu_dm_connector->num_modes =
				drm_add_edid_modes(connector, edid);

		amdgpu_dm_get_native_mode(connector);
	} else {
		amdgpu_dm_connector->num_modes = 0;
	}
}