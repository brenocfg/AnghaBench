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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rdma_dev_net {int /*<<< orphan*/  nl_sock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rdma_dev_net* rdma_net_to_dev_net (struct net*) ; 

int rdma_nl_unicast(struct net *net, struct sk_buff *skb, u32 pid)
{
	struct rdma_dev_net *rnet = rdma_net_to_dev_net(net);
	int err;

	err = netlink_unicast(rnet->nl_sock, skb, pid, MSG_DONTWAIT);
	return (err < 0) ? err : 0;
}