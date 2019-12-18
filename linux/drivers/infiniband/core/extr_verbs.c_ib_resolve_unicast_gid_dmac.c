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
struct TYPE_3__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_1__ roce; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {scalar_t__ raw; } ;
struct ib_global_route {int hop_limit; TYPE_2__ dgid; struct ib_gid_attr* sgid_attr; } ;
struct ib_gid_attr {scalar_t__ gid_type; int /*<<< orphan*/  gid; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_GID_TYPE_ROCE ; 
 int rdma_addr_find_l2_eth_by_grh (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,struct ib_gid_attr const*,int*) ; 
 struct ib_global_route* rdma_ah_retrieve_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_get_ll_mac (struct in6_addr*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_link_local_addr (struct in6_addr*) ; 

__attribute__((used)) static int ib_resolve_unicast_gid_dmac(struct ib_device *device,
				       struct rdma_ah_attr *ah_attr)
{
	struct ib_global_route *grh = rdma_ah_retrieve_grh(ah_attr);
	const struct ib_gid_attr *sgid_attr = grh->sgid_attr;
	int hop_limit = 0xff;
	int ret = 0;

	/* If destination is link local and source GID is RoCEv1,
	 * IP stack is not used.
	 */
	if (rdma_link_local_addr((struct in6_addr *)grh->dgid.raw) &&
	    sgid_attr->gid_type == IB_GID_TYPE_ROCE) {
		rdma_get_ll_mac((struct in6_addr *)grh->dgid.raw,
				ah_attr->roce.dmac);
		return ret;
	}

	ret = rdma_addr_find_l2_eth_by_grh(&sgid_attr->gid, &grh->dgid,
					   ah_attr->roce.dmac,
					   sgid_attr, &hop_limit);

	grh->hop_limit = hop_limit;
	return ret;
}