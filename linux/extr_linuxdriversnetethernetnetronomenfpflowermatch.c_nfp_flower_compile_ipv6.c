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
struct tc_cls_flower_offload {int /*<<< orphan*/  dissector; struct fl_flow_key* key; struct fl_flow_key* mask; } ;
struct nfp_flower_ipv6 {int /*<<< orphan*/  ip_ext; int /*<<< orphan*/  ipv6_dst; int /*<<< orphan*/  ipv6_src; } ;
struct flow_dissector_key_ipv6_addrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct fl_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_ipv6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_ip_ext (int /*<<< orphan*/ *,struct tc_cls_flower_offload*,int) ; 
 struct flow_dissector_key_ipv6_addrs* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fl_flow_key*) ; 

__attribute__((used)) static void
nfp_flower_compile_ipv6(struct nfp_flower_ipv6 *frame,
			struct tc_cls_flower_offload *flow,
			bool mask_version)
{
	struct fl_flow_key *target = mask_version ? flow->mask : flow->key;
	struct flow_dissector_key_ipv6_addrs *addr;

	memset(frame, 0, sizeof(struct nfp_flower_ipv6));

	if (dissector_uses_key(flow->dissector,
			       FLOW_DISSECTOR_KEY_IPV6_ADDRS)) {
		addr = skb_flow_dissector_target(flow->dissector,
						 FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						 target);
		frame->ipv6_src = addr->src;
		frame->ipv6_dst = addr->dst;
	}

	nfp_flower_compile_ip_ext(&frame->ip_ext, flow, mask_version);
}