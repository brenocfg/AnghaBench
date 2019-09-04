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
struct nfp_flower_ipv4_udp_tun {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; int /*<<< orphan*/  tun_id; } ;
struct flow_dissector_key_keyid {int /*<<< orphan*/  keyid; } ;
struct flow_dissector_key_ipv4_addrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct flow_dissector_key_ip {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct fl_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 int NFP_FL_TUN_VNI_OFFSET ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_flower_ipv4_udp_tun*,int /*<<< orphan*/ ,int) ; 
 void* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fl_flow_key*) ; 

__attribute__((used)) static void
nfp_flower_compile_ipv4_udp_tun(struct nfp_flower_ipv4_udp_tun *frame,
				struct tc_cls_flower_offload *flow,
				bool mask_version)
{
	struct fl_flow_key *target = mask_version ? flow->mask : flow->key;
	struct flow_dissector_key_ipv4_addrs *tun_ips;
	struct flow_dissector_key_keyid *vni;
	struct flow_dissector_key_ip *ip;

	memset(frame, 0, sizeof(struct nfp_flower_ipv4_udp_tun));

	if (dissector_uses_key(flow->dissector,
			       FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		u32 temp_vni;

		vni = skb_flow_dissector_target(flow->dissector,
						FLOW_DISSECTOR_KEY_ENC_KEYID,
						target);
		temp_vni = be32_to_cpu(vni->keyid) << NFP_FL_TUN_VNI_OFFSET;
		frame->tun_id = cpu_to_be32(temp_vni);
	}

	if (dissector_uses_key(flow->dissector,
			       FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS)) {
		tun_ips =
		   skb_flow_dissector_target(flow->dissector,
					     FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS,
					     target);
		frame->ip_src = tun_ips->src;
		frame->ip_dst = tun_ips->dst;
	}

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_ENC_IP)) {
		ip = skb_flow_dissector_target(flow->dissector,
					       FLOW_DISSECTOR_KEY_ENC_IP,
					       target);
		frame->tos = ip->tos;
		frame->ttl = ip->ttl;
	}
}