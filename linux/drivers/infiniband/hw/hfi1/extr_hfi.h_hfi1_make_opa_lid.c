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
typedef  scalar_t__ u32 ;
struct rdma_ah_attr {int dummy; } ;
struct ib_global_route {int /*<<< orphan*/  dgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 int /*<<< orphan*/  IB_MULTICAST_LID_BASE ; 
 int /*<<< orphan*/  OPA_LID_PERMISSIVE ; 
 int /*<<< orphan*/  OPA_MCAST_NR ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_is_opa_gid (int /*<<< orphan*/ *) ; 
 scalar_t__ opa_get_lid_from_gid (int /*<<< orphan*/ *) ; 
 scalar_t__ opa_get_mcast_base (int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,scalar_t__) ; 

__attribute__((used)) static inline void hfi1_make_opa_lid(struct rdma_ah_attr *attr)
{
	const struct ib_global_route *grh = rdma_ah_read_grh(attr);
	u32 dlid = rdma_ah_get_dlid(attr);

	/* Modify ah_attr.dlid to be in the 32 bit LID space.
	 * This is how the address will be laid out:
	 * Assuming MCAST_NR to be 4,
	 * 32 bit permissive LID = 0xFFFFFFFF
	 * Multicast LID range = 0xFFFFFFFE to 0xF0000000
	 * Unicast LID range = 0xEFFFFFFF to 1
	 * Invalid LID = 0
	 */
	if (ib_is_opa_gid(&grh->dgid))
		dlid = opa_get_lid_from_gid(&grh->dgid);
	else if ((dlid >= be16_to_cpu(IB_MULTICAST_LID_BASE)) &&
		 (dlid != be16_to_cpu(IB_LID_PERMISSIVE)) &&
		 (dlid != be32_to_cpu(OPA_LID_PERMISSIVE)))
		dlid = dlid - be16_to_cpu(IB_MULTICAST_LID_BASE) +
			opa_get_mcast_base(OPA_MCAST_NR);
	else if (dlid == be16_to_cpu(IB_LID_PERMISSIVE))
		dlid = be32_to_cpu(OPA_LID_PERMISSIVE);

	rdma_ah_set_dlid(attr, dlid);
}