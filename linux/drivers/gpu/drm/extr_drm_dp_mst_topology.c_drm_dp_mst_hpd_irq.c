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
typedef  int u8 ;
struct drm_dp_mst_topology_mgr {int sink_count; } ;

/* Variables and functions */
 int DP_DOWN_REP_MSG_RDY ; 
 int DP_UP_REQ_MSG_RDY ; 
 int drm_dp_mst_handle_down_rep (struct drm_dp_mst_topology_mgr*) ; 
 int drm_dp_mst_handle_up_req (struct drm_dp_mst_topology_mgr*) ; 
 int /*<<< orphan*/  drm_dp_mst_kick_tx (struct drm_dp_mst_topology_mgr*) ; 

int drm_dp_mst_hpd_irq(struct drm_dp_mst_topology_mgr *mgr, u8 *esi, bool *handled)
{
	int ret = 0;
	int sc;
	*handled = false;
	sc = esi[0] & 0x3f;

	if (sc != mgr->sink_count) {
		mgr->sink_count = sc;
		*handled = true;
	}

	if (esi[1] & DP_DOWN_REP_MSG_RDY) {
		ret = drm_dp_mst_handle_down_rep(mgr);
		*handled = true;
	}

	if (esi[1] & DP_UP_REQ_MSG_RDY) {
		ret |= drm_dp_mst_handle_up_req(mgr);
		*handled = true;
	}

	drm_dp_mst_kick_tx(mgr);
	return ret;
}