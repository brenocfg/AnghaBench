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
struct drm_dp_payload {scalar_t__ payload_state; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_PAYLOAD_LOCAL ; 
 int drm_dp_dpcd_write_payload (struct drm_dp_mst_topology_mgr*,int,struct drm_dp_payload*) ; 

__attribute__((used)) static int drm_dp_create_payload_step1(struct drm_dp_mst_topology_mgr *mgr,
				       int id,
				       struct drm_dp_payload *payload)
{
	int ret;

	ret = drm_dp_dpcd_write_payload(mgr, id, payload);
	if (ret < 0) {
		payload->payload_state = 0;
		return ret;
	}
	payload->payload_state = DP_PAYLOAD_LOCAL;
	return 0;
}