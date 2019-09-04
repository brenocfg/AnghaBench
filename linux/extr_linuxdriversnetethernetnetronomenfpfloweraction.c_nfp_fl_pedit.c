#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  key; int /*<<< orphan*/  dissector; } ;
struct tc_action {int dummy; } ;
struct TYPE_2__ {scalar_t__ len_lw; } ;
struct nfp_fl_set_tport {TYPE_1__ head; } ;
struct nfp_fl_set_ipv6_addr {TYPE_1__ head; } ;
struct nfp_fl_set_ip4_addrs {TYPE_1__ head; } ;
struct nfp_fl_set_eth {TYPE_1__ head; } ;
struct flow_dissector_key_basic {int /*<<< orphan*/  ip_proto; } ;
typedef  int /*<<< orphan*/  set_tport ;
typedef  int /*<<< orphan*/  set_ip_addr ;
typedef  int /*<<< orphan*/  set_ip6_src ;
typedef  int /*<<< orphan*/  set_ip6_dst ;
typedef  int /*<<< orphan*/  set_eth ;
typedef  enum pedit_header_type { ____Placeholder_pedit_header_type } pedit_header_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_TCP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_UDP ; 
 scalar_t__ TCA_CSUM_UPDATE_FLAG_IPV4HDR ; 
 scalar_t__ TCA_PEDIT_KEY_EX_CMD_SET ; 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_ETH 132 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_IP4 131 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_IP6 130 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_TCP 129 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_UDP 128 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,struct nfp_fl_set_tport*,size_t) ; 
 int /*<<< orphan*/  memset (struct nfp_fl_set_tport*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfp_fl_csum_l4_to_flag (int /*<<< orphan*/ ) ; 
 int nfp_fl_set_eth (struct tc_action const*,int,scalar_t__,struct nfp_fl_set_tport*) ; 
 int nfp_fl_set_ip4 (struct tc_action const*,int,scalar_t__,struct nfp_fl_set_tport*) ; 
 int nfp_fl_set_ip6 (struct tc_action const*,int,scalar_t__,struct nfp_fl_set_tport*,struct nfp_fl_set_tport*) ; 
 int nfp_fl_set_tport (struct tc_action const*,int,scalar_t__,struct nfp_fl_set_tport*,int /*<<< orphan*/ ) ; 
 struct flow_dissector_key_basic* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_pedit_cmd (struct tc_action const*,int) ; 
 int tcf_pedit_htype (struct tc_action const*,int) ; 
 int tcf_pedit_nkeys (struct tc_action const*) ; 
 scalar_t__ tcf_pedit_offset (struct tc_action const*,int) ; 

__attribute__((used)) static int
nfp_fl_pedit(const struct tc_action *action, struct tc_cls_flower_offload *flow,
	     char *nfp_action, int *a_len, u32 *csum_updated)
{
	struct nfp_fl_set_ipv6_addr set_ip6_dst, set_ip6_src;
	struct nfp_fl_set_ip4_addrs set_ip_addr;
	struct nfp_fl_set_tport set_tport;
	struct nfp_fl_set_eth set_eth;
	enum pedit_header_type htype;
	int idx, nkeys, err;
	size_t act_size = 0;
	u32 offset, cmd;
	u8 ip_proto = 0;

	memset(&set_ip6_dst, 0, sizeof(set_ip6_dst));
	memset(&set_ip6_src, 0, sizeof(set_ip6_src));
	memset(&set_ip_addr, 0, sizeof(set_ip_addr));
	memset(&set_tport, 0, sizeof(set_tport));
	memset(&set_eth, 0, sizeof(set_eth));
	nkeys = tcf_pedit_nkeys(action);

	for (idx = 0; idx < nkeys; idx++) {
		cmd = tcf_pedit_cmd(action, idx);
		htype = tcf_pedit_htype(action, idx);
		offset = tcf_pedit_offset(action, idx);

		if (cmd != TCA_PEDIT_KEY_EX_CMD_SET)
			return -EOPNOTSUPP;

		switch (htype) {
		case TCA_PEDIT_KEY_EX_HDR_TYPE_ETH:
			err = nfp_fl_set_eth(action, idx, offset, &set_eth);
			break;
		case TCA_PEDIT_KEY_EX_HDR_TYPE_IP4:
			err = nfp_fl_set_ip4(action, idx, offset, &set_ip_addr);
			break;
		case TCA_PEDIT_KEY_EX_HDR_TYPE_IP6:
			err = nfp_fl_set_ip6(action, idx, offset, &set_ip6_dst,
					     &set_ip6_src);
			break;
		case TCA_PEDIT_KEY_EX_HDR_TYPE_TCP:
			err = nfp_fl_set_tport(action, idx, offset, &set_tport,
					       NFP_FL_ACTION_OPCODE_SET_TCP);
			break;
		case TCA_PEDIT_KEY_EX_HDR_TYPE_UDP:
			err = nfp_fl_set_tport(action, idx, offset, &set_tport,
					       NFP_FL_ACTION_OPCODE_SET_UDP);
			break;
		default:
			return -EOPNOTSUPP;
		}
		if (err)
			return err;
	}

	if (dissector_uses_key(flow->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *basic;

		basic = skb_flow_dissector_target(flow->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  flow->key);
		ip_proto = basic->ip_proto;
	}

	if (set_eth.head.len_lw) {
		act_size = sizeof(set_eth);
		memcpy(nfp_action, &set_eth, act_size);
		*a_len += act_size;
	}
	if (set_ip_addr.head.len_lw) {
		nfp_action += act_size;
		act_size = sizeof(set_ip_addr);
		memcpy(nfp_action, &set_ip_addr, act_size);
		*a_len += act_size;

		/* Hardware will automatically fix IPv4 and TCP/UDP checksum. */
		*csum_updated |= TCA_CSUM_UPDATE_FLAG_IPV4HDR |
				nfp_fl_csum_l4_to_flag(ip_proto);
	}
	if (set_ip6_dst.head.len_lw && set_ip6_src.head.len_lw) {
		/* TC compiles set src and dst IPv6 address as a single action,
		 * the hardware requires this to be 2 separate actions.
		 */
		nfp_action += act_size;
		act_size = sizeof(set_ip6_src);
		memcpy(nfp_action, &set_ip6_src, act_size);
		*a_len += act_size;

		act_size = sizeof(set_ip6_dst);
		memcpy(&nfp_action[sizeof(set_ip6_src)], &set_ip6_dst,
		       act_size);
		*a_len += act_size;

		/* Hardware will automatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	} else if (set_ip6_dst.head.len_lw) {
		nfp_action += act_size;
		act_size = sizeof(set_ip6_dst);
		memcpy(nfp_action, &set_ip6_dst, act_size);
		*a_len += act_size;

		/* Hardware will automatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	} else if (set_ip6_src.head.len_lw) {
		nfp_action += act_size;
		act_size = sizeof(set_ip6_src);
		memcpy(nfp_action, &set_ip6_src, act_size);
		*a_len += act_size;

		/* Hardware will automatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	}
	if (set_tport.head.len_lw) {
		nfp_action += act_size;
		act_size = sizeof(set_tport);
		memcpy(nfp_action, &set_tport, act_size);
		*a_len += act_size;

		/* Hardware will automatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	}

	return 0;
}