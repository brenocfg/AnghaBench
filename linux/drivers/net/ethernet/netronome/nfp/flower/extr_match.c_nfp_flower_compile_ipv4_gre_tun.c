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
struct nfp_flower_ipv4_gre_tun {int /*<<< orphan*/  ip_ext; int /*<<< orphan*/  ipv4; void* tun_flags; int /*<<< orphan*/  tun_key; void* ethertype; } ;
struct flow_rule {int dummy; } ;
struct flow_match_enc_keyid {TYPE_2__* mask; TYPE_1__* key; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  keyid; } ;
struct TYPE_3__ {int /*<<< orphan*/  keyid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 int /*<<< orphan*/  NFP_FL_GRE_FLAG_KEY ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_keyid (struct flow_rule*,struct flow_match_enc_keyid*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_ipv4_gre_tun*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_tun_ip_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_tun_ipv4_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flow_cls_offload*) ; 

__attribute__((used)) static void
nfp_flower_compile_ipv4_gre_tun(struct nfp_flower_ipv4_gre_tun *ext,
				struct nfp_flower_ipv4_gre_tun *msk,
				struct flow_cls_offload *flow)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(flow);

	memset(ext, 0, sizeof(struct nfp_flower_ipv4_gre_tun));
	memset(msk, 0, sizeof(struct nfp_flower_ipv4_gre_tun));

	/* NVGRE is the only supported GRE tunnel type */
	ext->ethertype = cpu_to_be16(ETH_P_TEB);
	msk->ethertype = cpu_to_be16(~0);

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		ext->tun_key = match.key->keyid;
		msk->tun_key = match.mask->keyid;

		ext->tun_flags = cpu_to_be16(NFP_FL_GRE_FLAG_KEY);
		msk->tun_flags = cpu_to_be16(NFP_FL_GRE_FLAG_KEY);
	}

	nfp_flower_compile_tun_ipv4_addrs(&ext->ipv4, &msk->ipv4, flow);
	nfp_flower_compile_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, flow);
}