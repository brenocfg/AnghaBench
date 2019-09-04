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
struct drm_dp_mst_port {struct drm_dp_mst_branch* mstb; int /*<<< orphan*/  aux; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
#define  DP_PEER_DEVICE_DP_LEGACY_CONV 130 
#define  DP_PEER_DEVICE_MST_BRANCHING 129 
#define  DP_PEER_DEVICE_SST_SINK 128 
 int /*<<< orphan*/  drm_dp_mst_unregister_i2c_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_put_mst_branch_device (struct drm_dp_mst_branch*) ; 

__attribute__((used)) static void drm_dp_port_teardown_pdt(struct drm_dp_mst_port *port, int old_pdt)
{
	struct drm_dp_mst_branch *mstb;

	switch (old_pdt) {
	case DP_PEER_DEVICE_DP_LEGACY_CONV:
	case DP_PEER_DEVICE_SST_SINK:
		/* remove i2c over sideband */
		drm_dp_mst_unregister_i2c_bus(&port->aux);
		break;
	case DP_PEER_DEVICE_MST_BRANCHING:
		mstb = port->mstb;
		port->mstb = NULL;
		drm_dp_put_mst_branch_device(mstb);
		break;
	}
}