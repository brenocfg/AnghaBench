#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_dp_payload {int /*<<< orphan*/  payload_state; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pbn; } ;
struct drm_dp_mst_port {TYPE_1__ vcpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_PAYLOAD_REMOTE ; 
 int drm_dp_payload_send_msg (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_create_payload_step2(struct drm_dp_mst_topology_mgr *mgr,
				       struct drm_dp_mst_port *port,
				       int id,
				       struct drm_dp_payload *payload)
{
	int ret;
	ret = drm_dp_payload_send_msg(mgr, port, id, port->vcpi.pbn);
	if (ret < 0)
		return ret;
	payload->payload_state = DP_PAYLOAD_REMOTE;
	return ret;
}