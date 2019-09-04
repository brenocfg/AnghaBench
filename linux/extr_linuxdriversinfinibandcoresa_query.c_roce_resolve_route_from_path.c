#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int route_resolved; } ;
struct sa_path_rec {scalar_t__ rec_type; TYPE_2__ roce; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; } ;
struct rdma_dev_addr {scalar_t__ network; int /*<<< orphan*/ * net; int /*<<< orphan*/  bound_dev_if; } ;
struct ib_gid_attr {TYPE_1__* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RDMA_NETWORK_IPV4 ; 
 scalar_t__ RDMA_NETWORK_IPV6 ; 
 scalar_t__ SA_PATH_REC_TYPE_ROCE_V2 ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  rdma_gid2ip (struct sockaddr*,int /*<<< orphan*/ *) ; 
 int rdma_resolve_ip_route (struct sockaddr*,struct sockaddr*,struct rdma_dev_addr*) ; 

__attribute__((used)) static int roce_resolve_route_from_path(struct sa_path_rec *rec,
					const struct ib_gid_attr *attr)
{
	struct rdma_dev_addr dev_addr = {};
	union {
		struct sockaddr     _sockaddr;
		struct sockaddr_in  _sockaddr_in;
		struct sockaddr_in6 _sockaddr_in6;
	} sgid_addr, dgid_addr;
	int ret;

	if (rec->roce.route_resolved)
		return 0;
	if (!attr || !attr->ndev)
		return -EINVAL;

	dev_addr.bound_dev_if = attr->ndev->ifindex;
	/* TODO: Use net from the ib_gid_attr once it is added to it,
	 * until than, limit itself to init_net.
	 */
	dev_addr.net = &init_net;

	rdma_gid2ip(&sgid_addr._sockaddr, &rec->sgid);
	rdma_gid2ip(&dgid_addr._sockaddr, &rec->dgid);

	/* validate the route */
	ret = rdma_resolve_ip_route(&sgid_addr._sockaddr,
				    &dgid_addr._sockaddr, &dev_addr);
	if (ret)
		return ret;

	if ((dev_addr.network == RDMA_NETWORK_IPV4 ||
	     dev_addr.network == RDMA_NETWORK_IPV6) &&
	    rec->rec_type != SA_PATH_REC_TYPE_ROCE_V2)
		return -EINVAL;

	rec->roce.route_resolved = true;
	return 0;
}