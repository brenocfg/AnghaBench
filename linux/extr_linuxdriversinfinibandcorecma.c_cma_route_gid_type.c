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
typedef  enum rdma_network_type { ____Placeholder_rdma_network_type } rdma_network_type ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int RDMA_NETWORK_IPV4 ; 
 int RDMA_NETWORK_IPV6 ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static enum ib_gid_type cma_route_gid_type(enum rdma_network_type network_type,
					   unsigned long supported_gids,
					   enum ib_gid_type default_gid)
{
	if ((network_type == RDMA_NETWORK_IPV4 ||
	     network_type == RDMA_NETWORK_IPV6) &&
	    test_bit(IB_GID_TYPE_ROCE_UDP_ENCAP, &supported_gids))
		return IB_GID_TYPE_ROCE_UDP_ENCAP;

	return default_gid;
}