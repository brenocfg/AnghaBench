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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  extack; } ;
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; TYPE_2__ common; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp {TYPE_1__* bus_info; } ;
struct flow_dissector_key_tcp {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_TCP ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_TCP_FLAGS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_u32 (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct flow_dissector_key_tcp* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_flower_parse_tcp(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp_acl_rule_info *rulei,
				     struct tc_cls_flower_offload *f,
				     u8 ip_proto)
{
	struct flow_dissector_key_tcp *key, *mask;

	if (!dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_TCP))
		return 0;

	if (ip_proto != IPPROTO_TCP) {
		NL_SET_ERR_MSG_MOD(f->common.extack, "TCP keys supported only for TCP");
		dev_err(mlxsw_sp->bus_info->dev, "TCP keys supported only for TCP\n");
		return -EINVAL;
	}

	key = skb_flow_dissector_target(f->dissector,
					FLOW_DISSECTOR_KEY_TCP,
					f->key);
	mask = skb_flow_dissector_target(f->dissector,
					 FLOW_DISSECTOR_KEY_TCP,
					 f->mask);
	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_TCP_FLAGS,
				       ntohs(key->flags), ntohs(mask->flags));
	return 0;
}