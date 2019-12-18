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
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct ib_uverbs_qp_dest {int /*<<< orphan*/  port_num; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; int /*<<< orphan*/  dgid; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; scalar_t__ is_global; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_ah_find_type (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_ah_flags (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_make_grd (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_ah_attr_from_uverbs(struct ib_device *dev,
				     struct rdma_ah_attr *rdma_attr,
				     struct ib_uverbs_qp_dest *uverb_attr)
{
	rdma_attr->type = rdma_ah_find_type(dev, uverb_attr->port_num);
	if (uverb_attr->is_global) {
		rdma_ah_set_grh(rdma_attr, NULL,
				uverb_attr->flow_label,
				uverb_attr->sgid_index,
				uverb_attr->hop_limit,
				uverb_attr->traffic_class);
		rdma_ah_set_dgid_raw(rdma_attr, uverb_attr->dgid);
	} else {
		rdma_ah_set_ah_flags(rdma_attr, 0);
	}
	rdma_ah_set_dlid(rdma_attr, uverb_attr->dlid);
	rdma_ah_set_sl(rdma_attr, uverb_attr->sl);
	rdma_ah_set_path_bits(rdma_attr, uverb_attr->src_path_bits);
	rdma_ah_set_static_rate(rdma_attr, uverb_attr->static_rate);
	rdma_ah_set_port_num(rdma_attr, uverb_attr->port_num);
	rdma_ah_set_make_grd(rdma_attr, false);
}