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
struct udp_tunnel_info {scalar_t__ type; int /*<<< orphan*/  sa_family; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ vxlan_udp_port_number; } ;
struct enic {int /*<<< orphan*/  devcmd_lock; TYPE_1__ vxlan; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVERLAY_FEATURE_VXLAN ; 
 int /*<<< orphan*/  OVERLAY_OFFLOAD_DISABLE ; 
 scalar_t__ UDP_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int vnic_dev_overlay_offload_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_udp_tunnel_del(struct net_device *netdev,
				struct udp_tunnel_info *ti)
{
	struct enic *enic = netdev_priv(netdev);
	int err;

	spin_lock_bh(&enic->devcmd_lock);

	if ((ntohs(ti->port) != enic->vxlan.vxlan_udp_port_number) ||
	    ti->type != UDP_TUNNEL_TYPE_VXLAN) {
		netdev_info(netdev, "udp_tnl: port:%d, sa_family: %d, type: %d not offloaded",
			    ntohs(ti->port), ti->sa_family, ti->type);
		goto unlock;
	}

	err = vnic_dev_overlay_offload_ctrl(enic->vdev, OVERLAY_FEATURE_VXLAN,
					    OVERLAY_OFFLOAD_DISABLE);
	if (err) {
		netdev_err(netdev, "vxlan: del offload udp port: %d failed",
			   ntohs(ti->port));
		goto unlock;
	}

	enic->vxlan.vxlan_udp_port_number = 0;

	netdev_info(netdev, "vxlan: del offload udp port %d, family %d\n",
		    ntohs(ti->port), ti->sa_family);

unlock:
	spin_unlock_bh(&enic->devcmd_lock);
}