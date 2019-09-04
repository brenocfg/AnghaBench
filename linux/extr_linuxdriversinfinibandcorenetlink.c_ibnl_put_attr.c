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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ nla_put (struct sk_buff*,int,int,void*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 

int ibnl_put_attr(struct sk_buff *skb, struct nlmsghdr *nlh,
		  int len, void *data, int type)
{
	if (nla_put(skb, type, len, data)) {
		nlmsg_cancel(skb, nlh);
		return -EMSGSIZE;
	}
	return 0;
}