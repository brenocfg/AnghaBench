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
struct drm_dp_payload {int /*<<< orphan*/  payload_state; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_PAYLOAD_DELETE_LOCAL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_write_payload (struct drm_dp_mst_topology_mgr*,int,struct drm_dp_payload*) ; 
 int /*<<< orphan*/  drm_dp_payload_send_msg (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_destroy_payload_step1(struct drm_dp_mst_topology_mgr *mgr,
					struct drm_dp_mst_port *port,
					int id,
					struct drm_dp_payload *payload)
{
	DRM_DEBUG_KMS("\n");
	/* it's okay for these to fail */
	if (port) {
		drm_dp_payload_send_msg(mgr, port, id, 0);
	}

	drm_dp_dpcd_write_payload(mgr, id, payload);
	payload->payload_state = DP_PAYLOAD_DELETE_LOCAL;
	return 0;
}