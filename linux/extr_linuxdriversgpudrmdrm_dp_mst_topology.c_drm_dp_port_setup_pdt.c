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
typedef  int /*<<< orphan*/  u8 ;
struct drm_dp_mst_port {int pdt; TYPE_1__* mstb; int /*<<< orphan*/  mgr; int /*<<< orphan*/  aux; } ;
struct TYPE_2__ {struct drm_dp_mst_port* port_parent; int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
#define  DP_PEER_DEVICE_DP_LEGACY_CONV 130 
#define  DP_PEER_DEVICE_MST_BRANCHING 129 
#define  DP_PEER_DEVICE_SST_SINK 128 
 TYPE_1__* drm_dp_add_mst_branch_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_calculate_rad (struct drm_dp_mst_port*,int /*<<< orphan*/ *) ; 
 int drm_dp_mst_register_i2c_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool drm_dp_port_setup_pdt(struct drm_dp_mst_port *port)
{
	int ret;
	u8 rad[6], lct;
	bool send_link = false;
	switch (port->pdt) {
	case DP_PEER_DEVICE_DP_LEGACY_CONV:
	case DP_PEER_DEVICE_SST_SINK:
		/* add i2c over sideband */
		ret = drm_dp_mst_register_i2c_bus(&port->aux);
		break;
	case DP_PEER_DEVICE_MST_BRANCHING:
		lct = drm_dp_calculate_rad(port, rad);

		port->mstb = drm_dp_add_mst_branch_device(lct, rad);
		if (port->mstb) {
			port->mstb->mgr = port->mgr;
			port->mstb->port_parent = port;

			send_link = true;
		}
		break;
	}
	return send_link;
}