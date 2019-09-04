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
struct udp_tunnel_info {int type; int sa_family; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int flags; int vxlan_udp_port_number; scalar_t__ patch_level; } ;
struct enic {int /*<<< orphan*/  devcmd_lock; TYPE_1__ vxlan; int /*<<< orphan*/  vdev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int ENIC_VXLAN_MULTI_WQ ; 
 int ENIC_VXLAN_OUTER_IPV6 ; 
 int /*<<< orphan*/  OVERLAY_CFG_VXLAN_PORT_UPDATE ; 
 int /*<<< orphan*/  OVERLAY_FEATURE_VXLAN ; 
 int /*<<< orphan*/  RES_TYPE_WQ ; 
 int UDP_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int vnic_dev_get_res_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnic_dev_overlay_offload_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vnic_dev_overlay_offload_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void enic_udp_tunnel_add(struct net_device *netdev,
				struct udp_tunnel_info *ti)
{
	struct enic *enic = netdev_priv(netdev);
	__be16 port = ti->port;
	int err;

	spin_lock_bh(&enic->devcmd_lock);

	if (ti->type != UDP_TUNNEL_TYPE_VXLAN) {
		netdev_info(netdev, "udp_tnl: only vxlan tunnel offload supported");
		goto error;
	}

	switch (ti->sa_family) {
	case AF_INET6:
		if (!(enic->vxlan.flags & ENIC_VXLAN_OUTER_IPV6)) {
			netdev_info(netdev, "vxlan: only IPv4 offload supported");
			goto error;
		}
		/* Fall through */
	case AF_INET:
		break;
	default:
		goto error;
	}

	if (enic->vxlan.vxlan_udp_port_number) {
		if (ntohs(port) == enic->vxlan.vxlan_udp_port_number)
			netdev_warn(netdev, "vxlan: udp port already offloaded");
		else
			netdev_info(netdev, "vxlan: offload supported for only one UDP port");

		goto error;
	}
	if ((vnic_dev_get_res_count(enic->vdev, RES_TYPE_WQ) != 1) &&
	    !(enic->vxlan.flags & ENIC_VXLAN_MULTI_WQ)) {
		netdev_info(netdev, "vxlan: vxlan offload with multi wq not supported on this adapter");
		goto error;
	}

	err = vnic_dev_overlay_offload_cfg(enic->vdev,
					   OVERLAY_CFG_VXLAN_PORT_UPDATE,
					   ntohs(port));
	if (err)
		goto error;

	err = vnic_dev_overlay_offload_ctrl(enic->vdev, OVERLAY_FEATURE_VXLAN,
					    enic->vxlan.patch_level);
	if (err)
		goto error;

	enic->vxlan.vxlan_udp_port_number = ntohs(port);

	netdev_info(netdev, "vxlan fw-vers-%d: offload enabled for udp port: %d, sa_family: %d ",
		    (int)enic->vxlan.patch_level, ntohs(port), ti->sa_family);

	goto unlock;

error:
	netdev_info(netdev, "failed to offload udp port: %d, sa_family: %d, type: %d",
		    ntohs(port), ti->sa_family, ti->type);
unlock:
	spin_unlock_bh(&enic->devcmd_lock);
}