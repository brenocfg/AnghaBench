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
struct TYPE_4__ {scalar_t__ dmac; } ;
struct TYPE_6__ {scalar_t__ raw; } ;
struct TYPE_5__ {TYPE_3__ dgid; } ;
struct rdma_ah_attr {TYPE_1__ roce; TYPE_2__ grh; } ;
struct in6_addr {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ib_resolve_unicast_gid_dmac (struct ib_device*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  ip_eth_mc_map (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ipv6_addr_v4mapped (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_eth_mc_map (struct in6_addr*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ rdma_is_multicast_addr (struct in6_addr*) ; 

__attribute__((used)) static int ib_resolve_eth_dmac(struct ib_device *device,
			       struct rdma_ah_attr *ah_attr)
{
	int ret = 0;

	if (rdma_is_multicast_addr((struct in6_addr *)ah_attr->grh.dgid.raw)) {
		if (ipv6_addr_v4mapped((struct in6_addr *)ah_attr->grh.dgid.raw)) {
			__be32 addr = 0;

			memcpy(&addr, ah_attr->grh.dgid.raw + 12, 4);
			ip_eth_mc_map(addr, (char *)ah_attr->roce.dmac);
		} else {
			ipv6_eth_mc_map((struct in6_addr *)ah_attr->grh.dgid.raw,
					(char *)ah_attr->roce.dmac);
		}
	} else {
		ret = ib_resolve_unicast_gid_dmac(device, ah_attr);
	}
	return ret;
}