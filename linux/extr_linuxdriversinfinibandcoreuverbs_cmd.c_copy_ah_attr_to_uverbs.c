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
struct rdma_ah_attr {int dummy; } ;
struct ib_uverbs_qp_dest {int is_global; int /*<<< orphan*/  port_num; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_1__ dgid; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_static_rate (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 

__attribute__((used)) static void copy_ah_attr_to_uverbs(struct ib_uverbs_qp_dest *uverb_attr,
				   struct rdma_ah_attr *rdma_attr)
{
	const struct ib_global_route   *grh;

	uverb_attr->dlid              = rdma_ah_get_dlid(rdma_attr);
	uverb_attr->sl                = rdma_ah_get_sl(rdma_attr);
	uverb_attr->src_path_bits     = rdma_ah_get_path_bits(rdma_attr);
	uverb_attr->static_rate       = rdma_ah_get_static_rate(rdma_attr);
	uverb_attr->is_global         = !!(rdma_ah_get_ah_flags(rdma_attr) &
					 IB_AH_GRH);
	if (uverb_attr->is_global) {
		grh = rdma_ah_read_grh(rdma_attr);
		memcpy(uverb_attr->dgid, grh->dgid.raw, 16);
		uverb_attr->flow_label        = grh->flow_label;
		uverb_attr->sgid_index        = grh->sgid_index;
		uverb_attr->hop_limit         = grh->hop_limit;
		uverb_attr->traffic_class     = grh->traffic_class;
	}
	uverb_attr->port_num          = rdma_ah_get_port_num(rdma_attr);
}