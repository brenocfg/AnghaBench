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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  act_block; } ;
struct mlxsw_sp {TYPE_1__* bus_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETH_P_8021AD 129 
#define  ETH_P_8021Q 128 
 scalar_t__ FLOW_ACTION_VLAN_MANGLE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int mlxsw_afa_block_append_vlan_modify (int /*<<< orphan*/ ,int,int,int,struct netlink_ext_ack*) ; 

int mlxsw_sp_acl_rulei_act_vlan(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_rule_info *rulei,
				u32 action, u16 vid, u16 proto, u8 prio,
				struct netlink_ext_ack *extack)
{
	u8 ethertype;

	if (action == FLOW_ACTION_VLAN_MANGLE) {
		switch (proto) {
		case ETH_P_8021Q:
			ethertype = 0;
			break;
		case ETH_P_8021AD:
			ethertype = 1;
			break;
		default:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported VLAN protocol");
			dev_err(mlxsw_sp->bus_info->dev, "Unsupported VLAN protocol %#04x\n",
				proto);
			return -EINVAL;
		}

		return mlxsw_afa_block_append_vlan_modify(rulei->act_block,
							  vid, prio, ethertype,
							  extack);
	} else {
		NL_SET_ERR_MSG_MOD(extack, "Unsupported VLAN action");
		dev_err(mlxsw_sp->bus_info->dev, "Unsupported VLAN action\n");
		return -EINVAL;
	}
}