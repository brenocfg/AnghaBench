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
typedef  void* u16 ;
struct bnx2x_udp_tunnel {void* dst_port; scalar_t__ count; } ;
struct bnx2x_func_switch_update_params {int /*<<< orphan*/  changes; void* vxlan_dst_port; void* geneve_dst_port; } ;
struct TYPE_2__ {struct bnx2x_func_switch_update_params switch_update; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/  ramrod_flags; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {struct bnx2x_udp_tunnel* udp_tunnel_ports; int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,void*,void*,int) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_SWITCH_UPDATE ; 
 int /*<<< orphan*/  BNX2X_F_UPDATE_TUNNEL_CFG_CHNG ; 
 int /*<<< orphan*/  BNX2X_F_UPDATE_TUNNEL_INNER_RSS ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 size_t BNX2X_UDP_PORT_GENEVE ; 
 size_t BNX2X_UDP_PORT_VXLAN ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_RETRY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 

__attribute__((used)) static int bnx2x_udp_port_update(struct bnx2x *bp)
{
	struct bnx2x_func_switch_update_params *switch_update_params;
	struct bnx2x_func_state_params func_params = {NULL};
	struct bnx2x_udp_tunnel *udp_tunnel;
	u16 vxlan_port = 0, geneve_port = 0;
	int rc;

	switch_update_params = &func_params.params.switch_update;

	/* Prepare parameters for function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SWITCH_UPDATE;

	/* Function parameters */
	__set_bit(BNX2X_F_UPDATE_TUNNEL_CFG_CHNG,
		  &switch_update_params->changes);

	if (bp->udp_tunnel_ports[BNX2X_UDP_PORT_GENEVE].count) {
		udp_tunnel = &bp->udp_tunnel_ports[BNX2X_UDP_PORT_GENEVE];
		geneve_port = udp_tunnel->dst_port;
		switch_update_params->geneve_dst_port = geneve_port;
	}

	if (bp->udp_tunnel_ports[BNX2X_UDP_PORT_VXLAN].count) {
		udp_tunnel = &bp->udp_tunnel_ports[BNX2X_UDP_PORT_VXLAN];
		vxlan_port = udp_tunnel->dst_port;
		switch_update_params->vxlan_dst_port = vxlan_port;
	}

	/* Re-enable inner-rss for the offloaded UDP tunnels */
	__set_bit(BNX2X_F_UPDATE_TUNNEL_INNER_RSS,
		  &switch_update_params->changes);

	rc = bnx2x_func_state_change(bp, &func_params);
	if (rc)
		BNX2X_ERR("failed to set UDP dst port to %04x %04x (rc = 0x%x)\n",
			  vxlan_port, geneve_port, rc);
	else
		DP(BNX2X_MSG_SP,
		   "Configured UDP ports: Vxlan [%04x] Geneve [%04x]\n",
		   vxlan_port, geneve_port);

	return rc;
}