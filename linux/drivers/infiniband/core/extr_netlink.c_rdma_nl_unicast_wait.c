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
struct rdma_dev_net {int /*<<< orphan*/  nl_sock; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rdma_dev_net* rdma_net_to_dev_net (struct net*) ; 

int rdma_nl_unicast_wait(struct net *net, struct sk_buff *skb, __u32 pid)
{
	struct rdma_dev_net *rnet = rdma_net_to_dev_net(net);
	int err;

	err = netlink_unicast(rnet->nl_sock, skb, pid, 0);
	return (err < 0) ? err : 0;
}