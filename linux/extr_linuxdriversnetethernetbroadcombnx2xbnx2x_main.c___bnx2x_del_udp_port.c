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
typedef  scalar_t__ u16 ;
struct bnx2x_udp_tunnel {scalar_t__ dst_port; scalar_t__ count; } ;
struct bnx2x {int /*<<< orphan*/  dev; struct bnx2x_udp_tunnel* udp_tunnel_ports; } ;
typedef  enum bnx2x_udp_port_type { ____Placeholder_bnx2x_udp_port_type } bnx2x_udp_port_type ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_CHANGE_UDP_PORT ; 
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_rtnl (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bnx2x_del_udp_port(struct bnx2x *bp, u16 port,
				 enum bnx2x_udp_port_type type)
{
	struct bnx2x_udp_tunnel *udp_port = &bp->udp_tunnel_ports[type];

	if (!IS_PF(bp) || CHIP_IS_E1x(bp))
		return;

	if (!udp_port->count || udp_port->dst_port != port) {
		DP(BNX2X_MSG_SP, "Invalid UDP tunnel [%d] port\n",
		   type);
		return;
	}

	/* Remove reference, and make certain it's no longer in use */
	udp_port->count--;
	if (udp_port->count)
		return;
	udp_port->dst_port = 0;

	if (netif_running(bp->dev))
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_CHANGE_UDP_PORT, 0);
	else
		DP(BNX2X_MSG_SP, "Deleted UDP tunnel [%d] port %d\n",
		   type, port);
}