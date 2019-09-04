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
typedef  union rdma_network_hdr {int dummy; } rdma_network_hdr ;
typedef  int /*<<< orphan*/  u8 ;
struct ib_grh {scalar_t__ next_hdr; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_network_type { ____Placeholder_rdma_network_type } rdma_network_type ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int RDMA_NETWORK_IB ; 
 int RDMA_NETWORK_IPV4 ; 
 int RDMA_NETWORK_IPV6 ; 
 int RDMA_NETWORK_ROCE_V1 ; 
 int ib_get_rdma_header_version (union rdma_network_hdr*) ; 
 scalar_t__ rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum rdma_network_type ib_get_net_type_by_grh(struct ib_device *device,
						     u8 port_num,
						     const struct ib_grh *grh)
{
	int grh_version;

	if (rdma_protocol_ib(device, port_num))
		return RDMA_NETWORK_IB;

	grh_version = ib_get_rdma_header_version((union rdma_network_hdr *)grh);

	if (grh_version == 4)
		return RDMA_NETWORK_IPV4;

	if (grh->next_hdr == IPPROTO_UDP)
		return RDMA_NETWORK_IPV6;

	return RDMA_NETWORK_ROCE_V1;
}