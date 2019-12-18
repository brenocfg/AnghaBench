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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum rdma_network_type { ____Placeholder_rdma_network_type } rdma_network_type ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_CREATE_AH_TYPE_V1 ; 
 int /*<<< orphan*/  CMDQ_CREATE_AH_TYPE_V2IPV4 ; 
 int /*<<< orphan*/  CMDQ_CREATE_AH_TYPE_V2IPV6 ; 
#define  RDMA_NETWORK_IPV4 129 
#define  RDMA_NETWORK_IPV6 128 

__attribute__((used)) static u8 bnxt_re_stack_to_dev_nw_type(enum rdma_network_type ntype)
{
	u8 nw_type;

	switch (ntype) {
	case RDMA_NETWORK_IPV4:
		nw_type = CMDQ_CREATE_AH_TYPE_V2IPV4;
		break;
	case RDMA_NETWORK_IPV6:
		nw_type = CMDQ_CREATE_AH_TYPE_V2IPV6;
		break;
	default:
		nw_type = CMDQ_CREATE_AH_TYPE_V1;
		break;
	}
	return nw_type;
}