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
struct rdma_ah_attr {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  reserved; } ;
struct ib_uverbs_ah_attr {int is_global; scalar_t__ reserved; int /*<<< orphan*/  port_num; TYPE_2__ grh; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_1__ dgid; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 scalar_t__ RDMA_AH_ATTR_TYPE_OPA ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_conv_opa_to_ib (struct ib_device*,struct rdma_ah_attr*,struct rdma_ah_attr*) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_path_bits (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_static_rate (struct rdma_ah_attr*) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 

void ib_copy_ah_attr_to_user(struct ib_device *device,
			     struct ib_uverbs_ah_attr *dst,
			     struct rdma_ah_attr *ah_attr)
{
	struct rdma_ah_attr *src = ah_attr;
	struct rdma_ah_attr conv_ah;

	memset(&dst->grh.reserved, 0, sizeof(dst->grh.reserved));

	if ((ah_attr->type == RDMA_AH_ATTR_TYPE_OPA) &&
	    (rdma_ah_get_dlid(ah_attr) > be16_to_cpu(IB_LID_PERMISSIVE)) &&
	    (!rdma_ah_conv_opa_to_ib(device, &conv_ah, ah_attr)))
		src = &conv_ah;

	dst->dlid		   = rdma_ah_get_dlid(src);
	dst->sl			   = rdma_ah_get_sl(src);
	dst->src_path_bits	   = rdma_ah_get_path_bits(src);
	dst->static_rate	   = rdma_ah_get_static_rate(src);
	dst->is_global             = rdma_ah_get_ah_flags(src) &
					IB_AH_GRH ? 1 : 0;
	if (dst->is_global) {
		const struct ib_global_route *grh = rdma_ah_read_grh(src);

		memcpy(dst->grh.dgid, grh->dgid.raw, sizeof(grh->dgid));
		dst->grh.flow_label        = grh->flow_label;
		dst->grh.sgid_index        = grh->sgid_index;
		dst->grh.hop_limit         = grh->hop_limit;
		dst->grh.traffic_class     = grh->traffic_class;
	}
	dst->port_num		   = rdma_ah_get_port_num(src);
	dst->reserved 		   = 0;
}