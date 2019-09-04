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
typedef  int u32 ;
struct tc_cls_flower_offload {struct fl_flow_key* key; int /*<<< orphan*/  dissector; struct fl_flow_key* mask; } ;
struct nfp_flower_mac_mpls {void* mpls_lse; int /*<<< orphan*/  mac_src; int /*<<< orphan*/  mac_dst; } ;
struct flow_dissector_key_mpls {int /*<<< orphan*/  mpls_bos; int /*<<< orphan*/  mpls_tc; int /*<<< orphan*/  mpls_label; } ;
struct flow_dissector_key_eth_addrs {int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;
struct flow_dissector_key_basic {scalar_t__ n_proto; } ;
struct fl_flow_key {int dummy; } ;

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
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_mac_mpls*,int /*<<< orphan*/ ,int) ; 
 void* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fl_flow_key*) ; 

__attribute__((used)) static void
nfp_flower_compile_mac(struct nfp_flower_mac_mpls *frame,
		       struct tc_cls_flower_offload *flow,
		       bool mask_version)
{
	struct fl_flow_key *target = mask_version ? flow->mask : flow->key;
	struct flow_dissector_key_eth_addrs *addr;

	memset(frame, 0, sizeof(struct nfp_flower_mac_mpls));

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		addr = skb_flow_dissector_target(flow->dissector,
						 FLOW_DISSECTOR_KEY_ETH_ADDRS,
						 target);
		/* Populate mac frame. */
		ether_addr_copy(frame->mac_dst, &addr->dst[0]);
		ether_addr_copy(frame->mac_src, &addr->src[0]);
	}

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_MPLS)) {
		struct flow_dissector_key_mpls *mpls;
		u32 t_mpls;

		mpls = skb_flow_dissector_target(flow->dissector,
						 FLOW_DISSECTOR_KEY_MPLS,
						 target);

		t_mpls = FIELD_PREP(NFP_FLOWER_MASK_MPLS_LB, mpls->mpls_label) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_TC, mpls->mpls_tc) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_BOS, mpls->mpls_bos) |
			 NFP_FLOWER_MASK_MPLS_Q;

		frame->mpls_lse = cpu_to_be32(t_mpls);
	} else if (dissector_uses_key(flow->dissector,
				      FLOW_DISSECTOR_KEY_BASIC)) {
		/* Check for mpls ether type and set NFP_FLOWER_MASK_MPLS_Q
		 * bit, which indicates an mpls ether type but without any
		 * mpls fields.
		 */
		struct flow_dissector_key_basic *key_basic;

		key_basic = skb_flow_dissector_target(flow->dissector,
						      FLOW_DISSECTOR_KEY_BASIC,
						      flow->key);
		if (key_basic->n_proto == cpu_to_be16(ETH_P_MPLS_UC) ||
		    key_basic->n_proto == cpu_to_be16(ETH_P_MPLS_MC))
			frame->mpls_lse = cpu_to_be32(NFP_FLOWER_MASK_MPLS_Q);
	}
}