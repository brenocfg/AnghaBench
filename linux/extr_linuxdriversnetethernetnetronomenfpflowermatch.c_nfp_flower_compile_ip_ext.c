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
struct tc_cls_flower_offload {int /*<<< orphan*/  dissector; struct fl_flow_key* key; struct fl_flow_key* mask; } ;
struct nfp_flower_ip_ext {int /*<<< orphan*/  flags; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  proto; } ;
struct flow_dissector_key_tcp {int /*<<< orphan*/  flags; } ;
struct flow_dissector_key_ip {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct flow_dissector_key_control {int flags; } ;
struct flow_dissector_key_basic {int /*<<< orphan*/  ip_proto; } ;
struct fl_flow_key {int dummy; } ;

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
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fl_flow_key*) ; 

__attribute__((used)) static void
nfp_flower_compile_ip_ext(struct nfp_flower_ip_ext *frame,
			  struct tc_cls_flower_offload *flow,
			  bool mask_version)
{
	struct fl_flow_key *target = mask_version ? flow->mask : flow->key;

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *basic;

		basic = skb_flow_dissector_target(flow->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  target);
		frame->proto = basic->ip_proto;
	}

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_IP)) {
		struct flow_dissector_key_ip *flow_ip;

		flow_ip = skb_flow_dissector_target(flow->dissector,
						    FLOW_DISSECTOR_KEY_IP,
						    target);
		frame->tos = flow_ip->tos;
		frame->ttl = flow_ip->ttl;
	}

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_TCP)) {
		struct flow_dissector_key_tcp *tcp;
		u32 tcp_flags;

		tcp = skb_flow_dissector_target(flow->dissector,
						FLOW_DISSECTOR_KEY_TCP, target);
		tcp_flags = be16_to_cpu(tcp->flags);

		if (tcp_flags & TCPHDR_FIN)
			frame->flags |= NFP_FL_TCP_FLAG_FIN;
		if (tcp_flags & TCPHDR_SYN)
			frame->flags |= NFP_FL_TCP_FLAG_SYN;
		if (tcp_flags & TCPHDR_RST)
			frame->flags |= NFP_FL_TCP_FLAG_RST;
		if (tcp_flags & TCPHDR_PSH)
			frame->flags |= NFP_FL_TCP_FLAG_PSH;
		if (tcp_flags & TCPHDR_URG)
			frame->flags |= NFP_FL_TCP_FLAG_URG;
	}

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_dissector_key_control *key;

		key = skb_flow_dissector_target(flow->dissector,
						FLOW_DISSECTOR_KEY_CONTROL,
						target);
		if (key->flags & FLOW_DIS_IS_FRAGMENT)
			frame->flags |= NFP_FL_IP_FRAGMENTED;
		if (key->flags & FLOW_DIS_FIRST_FRAG)
			frame->flags |= NFP_FL_IP_FRAG_FIRST;
	}
}