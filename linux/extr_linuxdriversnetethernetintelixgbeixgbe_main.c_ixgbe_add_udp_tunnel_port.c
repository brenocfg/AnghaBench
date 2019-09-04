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
typedef  int u32 ;
struct udp_tunnel_info {scalar_t__ sa_family; int type; void* port; } ;
struct net_device {int dummy; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int flags; void* vxlan_port; void* geneve_port; struct ixgbe_hw hw; } ;
typedef  void* __be16 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int IXGBE_FLAG_GENEVE_OFFLOAD_CAPABLE ; 
 int IXGBE_FLAG_VXLAN_OFFLOAD_CAPABLE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VXLANCTRL ; 
 int IXGBE_VXLANCTRL_GENEVE_UDPPORT_SHIFT ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int ntohs (void*) ; 

__attribute__((used)) static void ixgbe_add_udp_tunnel_port(struct net_device *dev,
				      struct udp_tunnel_info *ti)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ixgbe_hw *hw = &adapter->hw;
	__be16 port = ti->port;
	u32 port_shift = 0;
	u32 reg;

	if (ti->sa_family != AF_INET)
		return;

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		if (!(adapter->flags & IXGBE_FLAG_VXLAN_OFFLOAD_CAPABLE))
			return;

		if (adapter->vxlan_port == port)
			return;

		if (adapter->vxlan_port) {
			netdev_info(dev,
				    "VXLAN port %d set, not adding port %d\n",
				    ntohs(adapter->vxlan_port),
				    ntohs(port));
			return;
		}

		adapter->vxlan_port = port;
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		if (!(adapter->flags & IXGBE_FLAG_GENEVE_OFFLOAD_CAPABLE))
			return;

		if (adapter->geneve_port == port)
			return;

		if (adapter->geneve_port) {
			netdev_info(dev,
				    "GENEVE port %d set, not adding port %d\n",
				    ntohs(adapter->geneve_port),
				    ntohs(port));
			return;
		}

		port_shift = IXGBE_VXLANCTRL_GENEVE_UDPPORT_SHIFT;
		adapter->geneve_port = port;
		break;
	default:
		return;
	}

	reg = IXGBE_READ_REG(hw, IXGBE_VXLANCTRL) | ntohs(port) << port_shift;
	IXGBE_WRITE_REG(hw, IXGBE_VXLANCTRL, reg);
}