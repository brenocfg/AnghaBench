#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct flow_match_ipv6_addrs {TYPE_6__* mask; TYPE_4__* key; } ;
struct flow_cls_offload {int /*<<< orphan*/  rule; } ;
struct TYPE_11__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_12__ {TYPE_5__ dst; TYPE_2__ src; } ;
struct TYPE_9__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_10__ {TYPE_3__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_32_63 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_64_95 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DST_IP_96_127 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_32_63 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_64_95 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SRC_IP_96_127 ; 
 int /*<<< orphan*/  flow_rule_match_ipv6_addrs (int /*<<< orphan*/ ,struct flow_match_ipv6_addrs*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_buf (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mlxsw_sp_flower_parse_ipv6(struct mlxsw_sp_acl_rule_info *rulei,
				       struct flow_cls_offload *f)
{
	struct flow_match_ipv6_addrs match;

	flow_rule_match_ipv6_addrs(f->rule, &match);

	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_96_127,
				       &match.key->src.s6_addr[0x0],
				       &match.mask->src.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_64_95,
				       &match.key->src.s6_addr[0x4],
				       &match.mask->src.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_32_63,
				       &match.key->src.s6_addr[0x8],
				       &match.mask->src.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       &match.key->src.s6_addr[0xC],
				       &match.mask->src.s6_addr[0xC], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_96_127,
				       &match.key->dst.s6_addr[0x0],
				       &match.mask->dst.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_64_95,
				       &match.key->dst.s6_addr[0x4],
				       &match.mask->dst.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_32_63,
				       &match.key->dst.s6_addr[0x8],
				       &match.mask->dst.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       &match.key->dst.s6_addr[0xC],
				       &match.mask->dst.s6_addr[0xC], 4);
}