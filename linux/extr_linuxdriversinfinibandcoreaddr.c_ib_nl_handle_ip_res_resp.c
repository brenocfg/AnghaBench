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
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EPERM ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NLM_F_REQUEST ; 
 scalar_t__ ib_nl_is_good_ip_resp (struct nlmsghdr*) ; 
 int /*<<< orphan*/  ib_nl_process_good_ip_rsep (struct nlmsghdr*) ; 

int ib_nl_handle_ip_res_resp(struct sk_buff *skb,
			     struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	if ((nlh->nlmsg_flags & NLM_F_REQUEST) ||
	    !(NETLINK_CB(skb).sk))
		return -EPERM;

	if (ib_nl_is_good_ip_resp(nlh))
		ib_nl_process_good_ip_rsep(nlh);

	return skb->len;
}