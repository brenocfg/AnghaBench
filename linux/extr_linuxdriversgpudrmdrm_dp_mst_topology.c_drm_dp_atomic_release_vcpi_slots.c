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
struct drm_dp_mst_topology_state {int avail_slots; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 scalar_t__ IS_ERR (struct drm_dp_mst_topology_state*) ; 
 int PTR_ERR (struct drm_dp_mst_topology_state*) ; 
 struct drm_dp_mst_topology_state* drm_atomic_get_mst_topology_state (struct drm_atomic_state*,struct drm_dp_mst_topology_mgr*) ; 

int drm_dp_atomic_release_vcpi_slots(struct drm_atomic_state *state,
				     struct drm_dp_mst_topology_mgr *mgr,
				     int slots)
{
	struct drm_dp_mst_topology_state *topology_state;

	topology_state = drm_atomic_get_mst_topology_state(state, mgr);
	if (IS_ERR(topology_state))
		return PTR_ERR(topology_state);

	/* We cannot rely on port->vcpi.num_slots to update
	 * topology_state->avail_slots as the port may not exist if the parent
	 * branch device was unplugged. This should be fixed by tracking
	 * per-port slot allocation in drm_dp_mst_topology_state instead of
	 * depending on the caller to tell us how many slots to release.
	 */
	topology_state->avail_slots += slots;
	DRM_DEBUG_KMS("vcpi slots released=%d, avail=%d\n",
			slots, topology_state->avail_slots);

	return 0;
}