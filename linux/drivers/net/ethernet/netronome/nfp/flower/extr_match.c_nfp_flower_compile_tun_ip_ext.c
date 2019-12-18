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
struct nfp_flower_tun_ip_ext {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct flow_rule {int dummy; } ;
struct flow_match_ip {TYPE_1__* mask; TYPE_2__* key; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_3__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IP ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_ip (struct flow_rule*,struct flow_match_ip*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_flower_compile_tun_ip_ext(struct nfp_flower_tun_ip_ext *ext,
			      struct nfp_flower_tun_ip_ext *msk,
			      struct flow_cls_offload *flow)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(flow);

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IP)) {
		struct flow_match_ip match;

		flow_rule_match_enc_ip(rule, &match);
		ext->tos = match.key->tos;
		ext->ttl = match.key->ttl;
		msk->tos = match.mask->tos;
		msk->ttl = match.mask->ttl;
	}
}