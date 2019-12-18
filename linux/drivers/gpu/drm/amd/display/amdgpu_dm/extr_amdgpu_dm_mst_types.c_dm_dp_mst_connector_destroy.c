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
struct amdgpu_encoder {int /*<<< orphan*/  port; int /*<<< orphan*/  base; struct amdgpu_encoder* edid; struct amdgpu_encoder* mst_encoder; } ;
struct amdgpu_dm_connector {int /*<<< orphan*/  port; int /*<<< orphan*/  base; struct amdgpu_dm_connector* edid; struct amdgpu_dm_connector* mst_encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_dp_mst_put_port_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_encoder*) ; 
 struct amdgpu_encoder* to_amdgpu_dm_connector (struct drm_connector*) ; 

__attribute__((used)) static void
dm_dp_mst_connector_destroy(struct drm_connector *connector)
{
	struct amdgpu_dm_connector *amdgpu_dm_connector = to_amdgpu_dm_connector(connector);
	struct amdgpu_encoder *amdgpu_encoder = amdgpu_dm_connector->mst_encoder;

	if (amdgpu_dm_connector->edid) {
		kfree(amdgpu_dm_connector->edid);
		amdgpu_dm_connector->edid = NULL;
	}

	drm_encoder_cleanup(&amdgpu_encoder->base);
	kfree(amdgpu_encoder);
	drm_connector_cleanup(connector);
	drm_dp_mst_put_port_malloc(amdgpu_dm_connector->port);
	kfree(amdgpu_dm_connector);
}