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
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  pbn_div; } ;
struct drm_dp_mst_port {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct drm_dp_mst_topology_state*) ; 
 int PTR_ERR (struct drm_dp_mst_topology_state*) ; 
 struct drm_dp_mst_topology_state* drm_atomic_get_mst_topology_state (struct drm_atomic_state*,struct drm_dp_mst_topology_mgr*) ; 
 struct drm_dp_mst_port* drm_dp_get_validated_port_ref (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_dp_put_port (struct drm_dp_mst_port*) ; 

int drm_dp_atomic_find_vcpi_slots(struct drm_atomic_state *state,
				  struct drm_dp_mst_topology_mgr *mgr,
				  struct drm_dp_mst_port *port, int pbn)
{
	struct drm_dp_mst_topology_state *topology_state;
	int req_slots;

	topology_state = drm_atomic_get_mst_topology_state(state, mgr);
	if (IS_ERR(topology_state))
		return PTR_ERR(topology_state);

	port = drm_dp_get_validated_port_ref(mgr, port);
	if (port == NULL)
		return -EINVAL;
	req_slots = DIV_ROUND_UP(pbn, mgr->pbn_div);
	DRM_DEBUG_KMS("vcpi slots req=%d, avail=%d\n",
			req_slots, topology_state->avail_slots);

	if (req_slots > topology_state->avail_slots) {
		drm_dp_put_port(port);
		return -ENOSPC;
	}

	topology_state->avail_slots -= req_slots;
	DRM_DEBUG_KMS("vcpi slots avail=%d", topology_state->avail_slots);

	drm_dp_put_port(port);
	return req_slots;
}