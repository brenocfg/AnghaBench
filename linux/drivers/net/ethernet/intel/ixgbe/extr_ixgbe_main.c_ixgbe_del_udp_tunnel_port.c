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
typedef  int /*<<< orphan*/  u32 ;
struct udp_tunnel_info {int type; scalar_t__ sa_family; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int flags; int /*<<< orphan*/  flags2; int /*<<< orphan*/  geneve_port; int /*<<< orphan*/  vxlan_port; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IXGBE_FLAG2_UDP_TUN_REREG_NEEDED ; 
 int IXGBE_FLAG_GENEVE_OFFLOAD_CAPABLE ; 
 int IXGBE_FLAG_VXLAN_OFFLOAD_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_VXLANCTRL_GENEVE_UDPPORT_MASK ; 
 int /*<<< orphan*/  IXGBE_VXLANCTRL_VXLAN_UDPPORT_MASK ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  ixgbe_clear_udp_tunnel_port (struct ixgbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_del_udp_tunnel_port(struct net_device *dev,
				      struct udp_tunnel_info *ti)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	u32 port_mask;

	if (ti->type != UDP_TUNNEL_TYPE_VXLAN &&
	    ti->type != UDP_TUNNEL_TYPE_GENEVE)
		return;

	if (ti->sa_family != AF_INET)
		return;

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		if (!(adapter->flags & IXGBE_FLAG_VXLAN_OFFLOAD_CAPABLE))
			return;

		if (adapter->vxlan_port != ti->port) {
			netdev_info(dev, "VXLAN port %d not found\n",
				    ntohs(ti->port));
			return;
		}

		port_mask = IXGBE_VXLANCTRL_VXLAN_UDPPORT_MASK;
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		if (!(adapter->flags & IXGBE_FLAG_GENEVE_OFFLOAD_CAPABLE))
			return;

		if (adapter->geneve_port != ti->port) {
			netdev_info(dev, "GENEVE port %d not found\n",
				    ntohs(ti->port));
			return;
		}

		port_mask = IXGBE_VXLANCTRL_GENEVE_UDPPORT_MASK;
		break;
	default:
		return;
	}

	ixgbe_clear_udp_tunnel_port(adapter, port_mask);
	adapter->flags2 |= IXGBE_FLAG2_UDP_TUN_REREG_NEEDED;
}