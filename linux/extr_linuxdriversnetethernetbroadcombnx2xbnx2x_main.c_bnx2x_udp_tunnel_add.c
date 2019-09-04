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
typedef  int /*<<< orphan*/  u16 ;
struct udp_tunnel_info {int type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_UDP_PORT_GENEVE ; 
 int /*<<< orphan*/  BNX2X_UDP_PORT_VXLAN ; 
#define  UDP_TUNNEL_TYPE_GENEVE 129 
#define  UDP_TUNNEL_TYPE_VXLAN 128 
 int /*<<< orphan*/  __bnx2x_add_udp_port (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_udp_tunnel_add(struct net_device *netdev,
				 struct udp_tunnel_info *ti)
{
	struct bnx2x *bp = netdev_priv(netdev);
	u16 t_port = ntohs(ti->port);

	switch (ti->type) {
	case UDP_TUNNEL_TYPE_VXLAN:
		__bnx2x_add_udp_port(bp, t_port, BNX2X_UDP_PORT_VXLAN);
		break;
	case UDP_TUNNEL_TYPE_GENEVE:
		__bnx2x_add_udp_port(bp, t_port, BNX2X_UDP_PORT_GENEVE);
		break;
	default:
		break;
	}
}