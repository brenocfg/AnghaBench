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
struct sock {int sk_sndtimeo; } ;
struct rdma_dev_net {struct sock* nl_sock; int /*<<< orphan*/  net; } ;
struct netlink_kernel_cfg {int /*<<< orphan*/  input; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  NETLINK_RDMA ; 
 struct sock* netlink_kernel_create (struct net*,int /*<<< orphan*/ ,struct netlink_kernel_cfg*) ; 
 int /*<<< orphan*/  rdma_nl_rcv ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 

int rdma_nl_net_init(struct rdma_dev_net *rnet)
{
	struct net *net = read_pnet(&rnet->net);
	struct netlink_kernel_cfg cfg = {
		.input	= rdma_nl_rcv,
	};
	struct sock *nls;

	nls = netlink_kernel_create(net, NETLINK_RDMA, &cfg);
	if (!nls)
		return -ENOMEM;

	nls->sk_sndtimeo = 10 * HZ;
	rnet->nl_sock = nls;
	return 0;
}