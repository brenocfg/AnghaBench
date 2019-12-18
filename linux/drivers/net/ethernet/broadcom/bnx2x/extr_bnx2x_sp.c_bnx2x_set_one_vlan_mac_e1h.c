#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mac_configuration_cmd {int dummy; } ;
struct bnx2x_raw_obj {scalar_t__ rdata; } ;
struct bnx2x_vlan_mac_obj {struct bnx2x_raw_obj raw; } ;
struct TYPE_5__ {int /*<<< orphan*/  vlan; int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {TYPE_1__ vlan_mac; } ;
struct TYPE_7__ {scalar_t__ cmd; TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_4__ cmd_data; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_VLAN_MAC_PENDING ; 
 scalar_t__ BNX2X_VLAN_MAC_ADD ; 
 int /*<<< orphan*/  ETH_VLAN_FILTER_CLASSIFY ; 
 int /*<<< orphan*/  bnx2x_vlan_mac_set_rdata_e1x (struct bnx2x*,struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mac_configuration_cmd*) ; 
 int /*<<< orphan*/  memset (struct mac_configuration_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_set_one_vlan_mac_e1h(struct bnx2x *bp,
				       struct bnx2x_vlan_mac_obj *o,
				       struct bnx2x_exeq_elem *elem,
				       int rule_idx, int cam_offset)
{
	struct bnx2x_raw_obj *raw = &o->raw;
	struct mac_configuration_cmd *config =
		(struct mac_configuration_cmd *)(raw->rdata);
	/* 57710 and 57711 do not support MOVE command,
	 * so it's either ADD or DEL
	 */
	bool add = (elem->cmd_data.vlan_mac.cmd == BNX2X_VLAN_MAC_ADD) ?
		true : false;

	/* Reset the ramrod data buffer */
	memset(config, 0, sizeof(*config));

	bnx2x_vlan_mac_set_rdata_e1x(bp, o, BNX2X_FILTER_VLAN_MAC_PENDING,
				     cam_offset, add,
				     elem->cmd_data.vlan_mac.u.vlan_mac.mac,
				     elem->cmd_data.vlan_mac.u.vlan_mac.vlan,
				     ETH_VLAN_FILTER_CLASSIFY, config);
}