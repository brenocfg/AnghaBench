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
struct drm_encoder {int dummy; } ;
struct drm_connector_helper_funcs {struct drm_encoder* (* best_encoder ) (struct drm_connector*) ;} ;
struct drm_connector {struct drm_connector_helper_funcs* helper_private; } ;
struct amdgpu_dm_connector {int num_modes; struct edid* edid; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_dm_connector_add_common_modes (struct drm_encoder*,struct drm_connector*) ; 
 int /*<<< orphan*/  amdgpu_dm_connector_ddc_get_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  amdgpu_dm_fbc_init (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_add_modes_noedid (struct drm_connector*,int,int) ; 
 int /*<<< orphan*/  drm_edid_is_valid (struct edid*) ; 
 struct drm_encoder* stub1 (struct drm_connector*) ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (struct drm_connector*) ; 

__attribute__((used)) static int amdgpu_dm_connector_get_modes(struct drm_connector *connector)
{
	const struct drm_connector_helper_funcs *helper =
			connector->helper_private;
	struct amdgpu_dm_connector *amdgpu_dm_connector =
			to_amdgpu_dm_connector(connector);
	struct drm_encoder *encoder;
	struct edid *edid = amdgpu_dm_connector->edid;

	encoder = helper->best_encoder(connector);

	if (!edid || !drm_edid_is_valid(edid)) {
		drm_add_modes_noedid(connector, 640, 480);
	} else {
		amdgpu_dm_connector_ddc_get_modes(connector, edid);
		amdgpu_dm_connector_add_common_modes(encoder, connector);
	}
	amdgpu_dm_fbc_init(connector);

	return amdgpu_dm_connector->num_modes;
}