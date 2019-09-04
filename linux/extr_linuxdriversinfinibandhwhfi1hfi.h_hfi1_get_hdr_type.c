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
typedef  scalar_t__ u32 ;
struct rdma_ah_attr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dgid; } ;

/* Variables and functions */
 int HFI1_PKT_TYPE_16B ; 
 int HFI1_PKT_TYPE_9B ; 
 int /*<<< orphan*/  OPA_LID_PERMISSIVE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int hfi1_get_packet_type (scalar_t__) ; 
 scalar_t__ ib_is_opa_gid (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 TYPE_1__* rdma_ah_read_grh (struct rdma_ah_attr*) ; 

__attribute__((used)) static inline bool hfi1_get_hdr_type(u32 lid, struct rdma_ah_attr *attr)
{
	/*
	 * If there was an incoming 16B packet with permissive
	 * LIDs, OPA GIDs would have been programmed when those
	 * packets were received. A 16B packet will have to
	 * be sent in response to that packet. Return a 16B
	 * header type if that's the case.
	 */
	if (rdma_ah_get_dlid(attr) == be32_to_cpu(OPA_LID_PERMISSIVE))
		return (ib_is_opa_gid(&rdma_ah_read_grh(attr)->dgid)) ?
			HFI1_PKT_TYPE_16B : HFI1_PKT_TYPE_9B;

	/*
	 * Return a 16B header type if either the the destination
	 * or source lid is extended.
	 */
	if (hfi1_get_packet_type(rdma_ah_get_dlid(attr)) == HFI1_PKT_TYPE_16B)
		return HFI1_PKT_TYPE_16B;

	return hfi1_get_packet_type(lid);
}