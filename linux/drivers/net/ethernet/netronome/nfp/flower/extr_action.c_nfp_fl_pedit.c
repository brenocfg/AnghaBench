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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_flower_pedit_acts {int /*<<< orphan*/  set_tport; int /*<<< orphan*/  set_ip6_tc_hl_fl; int /*<<< orphan*/  set_ip6_src; int /*<<< orphan*/  set_ip6_dst; int /*<<< orphan*/  set_ip_ttl_tos; int /*<<< orphan*/  set_ip_addr; int /*<<< orphan*/  set_eth; } ;
struct netlink_ext_ack {int dummy; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_2__ {int htype; int /*<<< orphan*/  offset; } ;
struct flow_action_entry {TYPE_1__ mangle; } ;
typedef  enum flow_action_mangle_base { ____Placeholder_flow_action_mangle_base } flow_action_mangle_base ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_TCP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_UDP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_ETH 132 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_IP4 131 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_IP6 130 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_TCP 129 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_UDP 128 
 int nfp_fl_set_eth (struct flow_action_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int nfp_fl_set_ip4 (struct flow_action_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int nfp_fl_set_ip6 (struct flow_action_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int nfp_fl_set_tport (struct flow_action_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
nfp_fl_pedit(const struct flow_action_entry *act,
	     struct flow_cls_offload *flow, char *nfp_action, int *a_len,
	     u32 *csum_updated, struct nfp_flower_pedit_acts *set_act,
	     struct netlink_ext_ack *extack)
{
	enum flow_action_mangle_base htype;
	u32 offset;

	htype = act->mangle.htype;
	offset = act->mangle.offset;

	switch (htype) {
	case TCA_PEDIT_KEY_EX_HDR_TYPE_ETH:
		return nfp_fl_set_eth(act, offset, &set_act->set_eth, extack);
	case TCA_PEDIT_KEY_EX_HDR_TYPE_IP4:
		return nfp_fl_set_ip4(act, offset, &set_act->set_ip_addr,
				      &set_act->set_ip_ttl_tos, extack);
	case TCA_PEDIT_KEY_EX_HDR_TYPE_IP6:
		return nfp_fl_set_ip6(act, offset, &set_act->set_ip6_dst,
				      &set_act->set_ip6_src,
				      &set_act->set_ip6_tc_hl_fl, extack);
	case TCA_PEDIT_KEY_EX_HDR_TYPE_TCP:
		return nfp_fl_set_tport(act, offset, &set_act->set_tport,
					NFP_FL_ACTION_OPCODE_SET_TCP, extack);
	case TCA_PEDIT_KEY_EX_HDR_TYPE_UDP:
		return nfp_fl_set_tport(act, offset, &set_act->set_tport,
					NFP_FL_ACTION_OPCODE_SET_UDP, extack);
	default:
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pedit on unsupported header");
		return -EOPNOTSUPP;
	}
}