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
struct fm10k_udp_port {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  geneve_port; int /*<<< orphan*/  vxlan_port; TYPE_2__ hw; } ;

/* Variables and functions */
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 scalar_t__ fm10k_mac_pf ; 
 struct fm10k_udp_port* fm10k_remove_tunnel_port (int /*<<< orphan*/ *,struct udp_tunnel_info*) ; 
 int /*<<< orphan*/  fm10k_restore_udp_port_info (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  kfree (struct fm10k_udp_port*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_udp_tunnel_del(struct net_device *dev,
				 struct udp_tunnel_info *ti)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_udp_port *port = NULL;

	if (interface->hw.mac.type != fm10k_mac_pf)
		return;

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		port = fm10k_remove_tunnel_port(&interface->vxlan_port, ti);
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		port = fm10k_remove_tunnel_port(&interface->geneve_port, ti);
		break;
	default:
		return;
	}

	/* if we did remove a port we need to free its memory */
	kfree(port);

	fm10k_restore_udp_port_info(interface);
}