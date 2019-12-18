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
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_dev_addr {int /*<<< orphan*/  network; } ;
struct net_device {scalar_t__ type; } ;
struct dst_entry {TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ ARPHRD_INFINIBAND ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  RDMA_NETWORK_IB ; 
 int /*<<< orphan*/  RDMA_NETWORK_IPV4 ; 
 int /*<<< orphan*/  RDMA_NETWORK_IPV6 ; 
 scalar_t__ has_gateway (struct dst_entry const*,scalar_t__) ; 
 int /*<<< orphan*/  rdma_copy_src_l2_addr (struct rdma_dev_addr*,TYPE_1__*) ; 
 int rdma_translate_ip (struct sockaddr const*,struct rdma_dev_addr*) ; 

__attribute__((used)) static int copy_src_l2_addr(struct rdma_dev_addr *dev_addr,
			    const struct sockaddr *dst_in,
			    const struct dst_entry *dst,
			    const struct net_device *ndev)
{
	int ret = 0;

	if (dst->dev->flags & IFF_LOOPBACK)
		ret = rdma_translate_ip(dst_in, dev_addr);
	else
		rdma_copy_src_l2_addr(dev_addr, dst->dev);

	/*
	 * If there's a gateway and type of device not ARPHRD_INFINIBAND,
	 * we're definitely in RoCE v2 (as RoCE v1 isn't routable) set the
	 * network type accordingly.
	 */
	if (has_gateway(dst, dst_in->sa_family) &&
	    ndev->type != ARPHRD_INFINIBAND)
		dev_addr->network = dst_in->sa_family == AF_INET ?
						RDMA_NETWORK_IPV4 :
						RDMA_NETWORK_IPV6;
	else
		dev_addr->network = RDMA_NETWORK_IB;

	return ret;
}