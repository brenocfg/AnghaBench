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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  extack; } ;
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; TYPE_1__ common; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp {TYPE_2__* bus_info; } ;
struct flow_dissector_key_ip {int ttl; int tos; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IP ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_IP_DSCP ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_IP_ECN ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_IP_TTL_ ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_u32 (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,int,int) ; 
 struct flow_dissector_key_ip* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_flower_parse_ip(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_acl_rule_info *rulei,
				    struct tc_cls_flower_offload *f,
				    u16 n_proto)
{
	struct flow_dissector_key_ip *key, *mask;

	if (!dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_IP))
		return 0;

	if (n_proto != ETH_P_IP && n_proto != ETH_P_IPV6) {
		NL_SET_ERR_MSG_MOD(f->common.extack, "IP keys supported only for IPv4/6");
		dev_err(mlxsw_sp->bus_info->dev, "IP keys supported only for IPv4/6\n");
		return -EINVAL;
	}

	key = skb_flow_dissector_target(f->dissector,
					FLOW_DISSECTOR_KEY_IP,
					f->key);
	mask = skb_flow_dissector_target(f->dissector,
					 FLOW_DISSECTOR_KEY_IP,
					 f->mask);
	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_IP_TTL_,
				       key->ttl, mask->ttl);

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_IP_ECN,
				       key->tos & 0x3, mask->tos & 0x3);

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_IP_DSCP,
				       key->tos >> 6, mask->tos >> 6);

	return 0;
}