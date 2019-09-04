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
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct flow_dissector_key_ipv4_addrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_0_31 ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_buf (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,char*,char*,int) ; 
 struct flow_dissector_key_ipv4_addrs* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_flower_parse_ipv4(struct mlxsw_sp_acl_rule_info *rulei,
				       struct tc_cls_flower_offload *f)
{
	struct flow_dissector_key_ipv4_addrs *key =
		skb_flow_dissector_target(f->dissector,
					  FLOW_DISSECTOR_KEY_IPV4_ADDRS,
					  f->key);
	struct flow_dissector_key_ipv4_addrs *mask =
		skb_flow_dissector_target(f->dissector,
					  FLOW_DISSECTOR_KEY_IPV4_ADDRS,
					  f->mask);

	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       (char *) &key->src,
				       (char *) &mask->src, 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       (char *) &key->dst,
				       (char *) &mask->dst, 4);
}