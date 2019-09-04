#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udp_tunnel_info {int type; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  geneve_port; int /*<<< orphan*/  vxlan_port; TYPE_2__ hw; } ;

/* Variables and functions */
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  fm10k_insert_tunnel_port (int /*<<< orphan*/ *,struct udp_tunnel_info*) ; 
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_restore_udp_port_info (struct fm10k_intfc*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_udp_tunnel_add(struct net_device *dev,
				 struct udp_tunnel_info *ti)
{
	struct fm10k_intfc *interface = netdev_priv(dev);

	/* only the PF supports configuring tunnels */
	if (interface->hw.mac.type != fm10k_mac_pf)
		return;

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		fm10k_insert_tunnel_port(&interface->vxlan_port, ti);
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		fm10k_insert_tunnel_port(&interface->geneve_port, ti);
		break;
	default:
		return;
	}

	fm10k_restore_udp_port_info(interface);
}