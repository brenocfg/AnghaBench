#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bound_dev_if; int /*<<< orphan*/  net; } ;
struct TYPE_4__ {scalar_t__ ss_family; } ;
struct rdma_addr {TYPE_2__ dev_addr; TYPE_1__ src_addr; } ;
struct TYPE_6__ {struct rdma_addr addr; } ;
struct rdma_cm_id {scalar_t__ port_num; TYPE_3__ route; } ;
struct net_device {scalar_t__ ifindex; } ;
struct cma_req_info {scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 int /*<<< orphan*/  cma_is_req_ipv6_ll (struct cma_req_info const*) ; 
 int /*<<< orphan*/  dev_net (struct net_device const*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cma_match_net_dev(const struct rdma_cm_id *id,
			      const struct net_device *net_dev,
			      const struct cma_req_info *req)
{
	const struct rdma_addr *addr = &id->route.addr;

	if (!net_dev)
		/* This request is an AF_IB request */
		return (!id->port_num || id->port_num == req->port) &&
		       (addr->src_addr.ss_family == AF_IB);

	/*
	 * If the request is not for IPv6 link local, allow matching
	 * request to any netdevice of the one or multiport rdma device.
	 */
	if (!cma_is_req_ipv6_ll(req))
		return true;
	/*
	 * Net namespaces must match, and if the listner is listening
	 * on a specific netdevice than netdevice must match as well.
	 */
	if (net_eq(dev_net(net_dev), addr->dev_addr.net) &&
	    (!!addr->dev_addr.bound_dev_if ==
	     (addr->dev_addr.bound_dev_if == net_dev->ifindex)))
		return true;
	else
		return false;
}