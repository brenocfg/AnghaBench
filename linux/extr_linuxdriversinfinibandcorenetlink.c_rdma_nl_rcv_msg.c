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
struct sk_buff {int dummy; } ;
struct rdma_nl_cbs {int flags; int (* doit ) (struct sk_buff*,struct nlmsghdr*,struct netlink_ext_ack*) ;scalar_t__ dump; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_dump_control {scalar_t__ dump; } ;
struct TYPE_2__ {struct rdma_nl_cbs* cb_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int NLM_F_DUMP ; 
 int RDMA_NL_ADMIN_PERM ; 
 unsigned int RDMA_NL_GET_CLIENT (int) ; 
 unsigned int RDMA_NL_GET_OP (int) ; 
 unsigned int RDMA_NL_IWCM ; 
 unsigned int RDMA_NL_LS ; 
 unsigned int RDMA_NL_RDMA_CM ; 
 int /*<<< orphan*/  is_nl_valid (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netlink_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int netlink_dump_start (int /*<<< orphan*/ ,struct sk_buff*,struct nlmsghdr*,struct netlink_dump_control*) ; 
 int /*<<< orphan*/  nls ; 
 TYPE_1__* rdma_nl_types ; 
 int stub1 (struct sk_buff*,struct nlmsghdr*,struct netlink_ext_ack*) ; 
 int stub2 (struct sk_buff*,struct nlmsghdr*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int rdma_nl_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh,
			   struct netlink_ext_ack *extack)
{
	int type = nlh->nlmsg_type;
	unsigned int index = RDMA_NL_GET_CLIENT(type);
	unsigned int op = RDMA_NL_GET_OP(type);
	const struct rdma_nl_cbs *cb_table;

	if (!is_nl_valid(index, op))
		return -EINVAL;

	cb_table = rdma_nl_types[index].cb_table;

	if ((cb_table[op].flags & RDMA_NL_ADMIN_PERM) &&
	    !netlink_capable(skb, CAP_NET_ADMIN))
		return -EPERM;

	/*
	 * LS responses overload the 0x100 (NLM_F_ROOT) flag.  Don't
	 * mistakenly call the .dump() function.
	 */
	if (index == RDMA_NL_LS) {
		if (cb_table[op].doit)
			return cb_table[op].doit(skb, nlh, extack);
		return -EINVAL;
	}
	/* FIXME: Convert IWCM to properly handle doit callbacks */
	if ((nlh->nlmsg_flags & NLM_F_DUMP) || index == RDMA_NL_RDMA_CM ||
	    index == RDMA_NL_IWCM) {
		struct netlink_dump_control c = {
			.dump = cb_table[op].dump,
		};
		if (c.dump)
			return netlink_dump_start(nls, skb, nlh, &c);
		return -EINVAL;
	}

	if (cb_table[op].doit)
		return cb_table[op].doit(skb, nlh, extack);

	return 0;
}