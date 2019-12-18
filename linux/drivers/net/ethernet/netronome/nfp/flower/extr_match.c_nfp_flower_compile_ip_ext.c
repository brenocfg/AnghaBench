#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nfp_flower_ip_ext {int /*<<< orphan*/  flags; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  proto; } ;
struct flow_rule {int dummy; } ;
struct flow_match_tcp {TYPE_6__* mask; TYPE_5__* key; } ;
struct flow_match_ip {TYPE_4__* mask; TYPE_3__* key; } ;
struct flow_match_control {TYPE_8__* mask; TYPE_7__* key; } ;
struct flow_match_basic {TYPE_2__* mask; TYPE_1__* key; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_16__ {int flags; } ;
struct TYPE_15__ {int flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_11__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip_proto; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_TCP ; 
 int FLOW_DIS_FIRST_FRAG ; 
 int FLOW_DIS_IS_FRAGMENT ; 
 int /*<<< orphan*/  NFP_FL_IP_FRAGMENTED ; 
 int /*<<< orphan*/  NFP_FL_IP_FRAG_FIRST ; 
 int /*<<< orphan*/  NFP_FL_TCP_FLAG_FIN ; 
 int /*<<< orphan*/  NFP_FL_TCP_FLAG_PSH ; 
 int /*<<< orphan*/  NFP_FL_TCP_FLAG_RST ; 
 int /*<<< orphan*/  NFP_FL_TCP_FLAG_SYN ; 
 int /*<<< orphan*/  NFP_FL_TCP_FLAG_URG ; 
 int TCPHDR_FIN ; 
 int TCPHDR_PSH ; 
 int TCPHDR_RST ; 
 int TCPHDR_SYN ; 
 int TCPHDR_URG ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 int /*<<< orphan*/  flow_rule_match_control (struct flow_rule*,struct flow_match_control*) ; 
 int /*<<< orphan*/  flow_rule_match_ip (struct flow_rule*,struct flow_match_ip*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_tcp (struct flow_rule*,struct flow_match_tcp*) ; 

__attribute__((used)) static void
nfp_flower_compile_ip_ext(struct nfp_flower_ip_ext *ext,
			  struct nfp_flower_ip_ext *msk,
			  struct flow_cls_offload *flow)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(flow);

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ext->proto = match.key->ip_proto;
		msk->proto = match.mask->ip_proto;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) {
		struct flow_match_ip match;

		flow_rule_match_ip(rule, &match);
		ext->tos = match.key->tos;
		ext->ttl = match.key->ttl;
		msk->tos = match.mask->tos;
		msk->ttl = match.mask->ttl;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP)) {
		u16 tcp_flags, tcp_flags_mask;
		struct flow_match_tcp match;

		flow_rule_match_tcp(rule, &match);
		tcp_flags = be16_to_cpu(match.key->flags);
		tcp_flags_mask = be16_to_cpu(match.mask->flags);

		if (tcp_flags & TCPHDR_FIN)
			ext->flags |= NFP_FL_TCP_FLAG_FIN;
		if (tcp_flags_mask & TCPHDR_FIN)
			msk->flags |= NFP_FL_TCP_FLAG_FIN;

		if (tcp_flags & TCPHDR_SYN)
			ext->flags |= NFP_FL_TCP_FLAG_SYN;
		if (tcp_flags_mask & TCPHDR_SYN)
			msk->flags |= NFP_FL_TCP_FLAG_SYN;

		if (tcp_flags & TCPHDR_RST)
			ext->flags |= NFP_FL_TCP_FLAG_RST;
		if (tcp_flags_mask & TCPHDR_RST)
			msk->flags |= NFP_FL_TCP_FLAG_RST;

		if (tcp_flags & TCPHDR_PSH)
			ext->flags |= NFP_FL_TCP_FLAG_PSH;
		if (tcp_flags_mask & TCPHDR_PSH)
			msk->flags |= NFP_FL_TCP_FLAG_PSH;

		if (tcp_flags & TCPHDR_URG)
			ext->flags |= NFP_FL_TCP_FLAG_URG;
		if (tcp_flags_mask & TCPHDR_URG)
			msk->flags |= NFP_FL_TCP_FLAG_URG;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_match_control match;

		flow_rule_match_control(rule, &match);
		if (match.key->flags & FLOW_DIS_IS_FRAGMENT)
			ext->flags |= NFP_FL_IP_FRAGMENTED;
		if (match.mask->flags & FLOW_DIS_IS_FRAGMENT)
			msk->flags |= NFP_FL_IP_FRAGMENTED;
		if (match.key->flags & FLOW_DIS_FIRST_FRAG)
			ext->flags |= NFP_FL_IP_FRAG_FIRST;
		if (match.mask->flags & FLOW_DIS_FIRST_FRAG)
			msk->flags |= NFP_FL_IP_FRAG_FIRST;
	}
}