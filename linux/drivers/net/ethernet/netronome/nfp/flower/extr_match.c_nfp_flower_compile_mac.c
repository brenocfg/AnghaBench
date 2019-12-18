#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nfp_flower_mac_mpls {void* mpls_lse; int /*<<< orphan*/  mac_src; int /*<<< orphan*/  mac_dst; } ;
struct flow_rule {int dummy; } ;
struct flow_match_mpls {TYPE_4__* mask; TYPE_3__* key; } ;
struct flow_match_eth_addrs {TYPE_2__* mask; TYPE_1__* key; } ;
struct flow_match_basic {TYPE_5__* key; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_10__ {scalar_t__ n_proto; } ;
struct TYPE_9__ {int /*<<< orphan*/  mpls_bos; int /*<<< orphan*/  mpls_tc; int /*<<< orphan*/  mpls_label; } ;
struct TYPE_8__ {int /*<<< orphan*/  mpls_bos; int /*<<< orphan*/  mpls_tc; int /*<<< orphan*/  mpls_label; } ;
struct TYPE_7__ {int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;
struct TYPE_6__ {int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_MPLS_MC ; 
 int /*<<< orphan*/  ETH_P_MPLS_UC ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_MPLS ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_MPLS_BOS ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_MPLS_LB ; 
 int NFP_FLOWER_MASK_MPLS_Q ; 
 int /*<<< orphan*/  NFP_FLOWER_MASK_MPLS_TC ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 int /*<<< orphan*/  flow_rule_match_eth_addrs (struct flow_rule*,struct flow_match_eth_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_mpls (struct flow_rule*,struct flow_match_mpls*) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_mac_mpls*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nfp_flower_compile_mac(struct nfp_flower_mac_mpls *ext,
		       struct nfp_flower_mac_mpls *msk,
		       struct flow_cls_offload *flow)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(flow);

	memset(ext, 0, sizeof(struct nfp_flower_mac_mpls));
	memset(msk, 0, sizeof(struct nfp_flower_mac_mpls));

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		/* Populate mac frame. */
		ether_addr_copy(ext->mac_dst, &match.key->dst[0]);
		ether_addr_copy(ext->mac_src, &match.key->src[0]);
		ether_addr_copy(msk->mac_dst, &match.mask->dst[0]);
		ether_addr_copy(msk->mac_src, &match.mask->src[0]);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_MPLS)) {
		struct flow_match_mpls match;
		u32 t_mpls;

		flow_rule_match_mpls(rule, &match);
		t_mpls = FIELD_PREP(NFP_FLOWER_MASK_MPLS_LB, match.key->mpls_label) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_TC, match.key->mpls_tc) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_BOS, match.key->mpls_bos) |
			 NFP_FLOWER_MASK_MPLS_Q;
		ext->mpls_lse = cpu_to_be32(t_mpls);
		t_mpls = FIELD_PREP(NFP_FLOWER_MASK_MPLS_LB, match.mask->mpls_label) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_TC, match.mask->mpls_tc) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_BOS, match.mask->mpls_bos) |
			 NFP_FLOWER_MASK_MPLS_Q;
		msk->mpls_lse = cpu_to_be32(t_mpls);
	} else if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		/* Check for mpls ether type and set NFP_FLOWER_MASK_MPLS_Q
		 * bit, which indicates an mpls ether type but without any
		 * mpls fields.
		 */
		struct flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		if (match.key->n_proto == cpu_to_be16(ETH_P_MPLS_UC) ||
		    match.key->n_proto == cpu_to_be16(ETH_P_MPLS_MC)) {
			ext->mpls_lse = cpu_to_be32(NFP_FLOWER_MASK_MPLS_Q);
			msk->mpls_lse = cpu_to_be32(NFP_FLOWER_MASK_MPLS_Q);
		}
	}
}