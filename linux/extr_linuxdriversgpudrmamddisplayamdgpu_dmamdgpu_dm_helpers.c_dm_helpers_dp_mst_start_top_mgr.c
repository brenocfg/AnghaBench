#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dc_link {struct amdgpu_dm_connector* priv; } ;
struct dc_context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct amdgpu_dm_connector {int /*<<< orphan*/  mst_mgr; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,struct amdgpu_dm_connector*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_mst_topology_mgr_set_mst (int /*<<< orphan*/ *,int) ; 

bool dm_helpers_dp_mst_start_top_mgr(
		struct dc_context *ctx,
		const struct dc_link *link,
		bool boot)
{
	struct amdgpu_dm_connector *aconnector = link->priv;

	if (!aconnector) {
			DRM_ERROR("Failed to found connector for link!");
			return false;
	}

	if (boot) {
		DRM_INFO("DM_MST: Differing MST start on aconnector: %p [id: %d]\n",
					aconnector, aconnector->base.base.id);
		return true;
	}

	DRM_INFO("DM_MST: starting TM on aconnector: %p [id: %d]\n",
			aconnector, aconnector->base.base.id);

	return (drm_dp_mst_topology_mgr_set_mst(&aconnector->mst_mgr, true) == 0);
}