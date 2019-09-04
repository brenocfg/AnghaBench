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
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * s6_addr; } ;
struct flow_dissector_key_ipv6_addrs {TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_32_63 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_64_95 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_96_127 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_32_63 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_64_95 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_96_127 ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_buf (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct flow_dissector_key_ipv6_addrs* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_flower_parse_ipv6(struct mlxsw_sp_acl_rule_info *rulei,
				       struct tc_cls_flower_offload *f)
{
	struct flow_dissector_key_ipv6_addrs *key =
		skb_flow_dissector_target(f->dissector,
					  FLOW_DISSECTOR_KEY_IPV6_ADDRS,
					  f->key);
	struct flow_dissector_key_ipv6_addrs *mask =
		skb_flow_dissector_target(f->dissector,
					  FLOW_DISSECTOR_KEY_IPV6_ADDRS,
					  f->mask);

	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_96_127,
				       &key->src.s6_addr[0x0],
				       &mask->src.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_64_95,
				       &key->src.s6_addr[0x4],
				       &mask->src.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_32_63,
				       &key->src.s6_addr[0x8],
				       &mask->src.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       &key->src.s6_addr[0xC],
				       &mask->src.s6_addr[0xC], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_96_127,
				       &key->dst.s6_addr[0x0],
				       &mask->dst.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_64_95,
				       &key->dst.s6_addr[0x4],
				       &mask->dst.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_32_63,
				       &key->dst.s6_addr[0x8],
				       &mask->dst.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       &key->dst.s6_addr[0xC],
				       &mask->dst.s6_addr[0xC], 4);
}