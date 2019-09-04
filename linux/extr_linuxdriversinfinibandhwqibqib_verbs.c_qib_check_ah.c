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
struct rdma_ah_attr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int /*<<< orphan*/  IB_MULTICAST_LID_BASE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 scalar_t__ rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int rdma_ah_get_sl (struct rdma_ah_attr*) ; 

int qib_check_ah(struct ib_device *ibdev, struct rdma_ah_attr *ah_attr)
{
	if (rdma_ah_get_sl(ah_attr) > 15)
		return -EINVAL;

	if (rdma_ah_get_dlid(ah_attr) == 0)
		return -EINVAL;
	if (rdma_ah_get_dlid(ah_attr) >=
		be16_to_cpu(IB_MULTICAST_LID_BASE) &&
	    rdma_ah_get_dlid(ah_attr) !=
		be16_to_cpu(IB_LID_PERMISSIVE) &&
	    !(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		return -EINVAL;

	return 0;
}