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
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int,int) ; 
 void* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

void *ibnl_put_msg(struct sk_buff *skb, struct nlmsghdr **nlh, int seq,
		   int len, int client, int op, int flags)
{
	*nlh = nlmsg_put(skb, 0, seq, RDMA_NL_GET_TYPE(client, op), len, flags);
	if (!*nlh)
		return NULL;
	return nlmsg_data(*nlh);
}