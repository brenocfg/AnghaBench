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
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_2__ dgid; } ;
struct rxe_av {int /*<<< orphan*/  port_num; TYPE_3__ grh; } ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_1__ dgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_AH_GRH ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ib_global_route* rdma_ah_retrieve_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_set_ah_flags (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 

void rxe_av_to_attr(struct rxe_av *av, struct rdma_ah_attr *attr)
{
	struct ib_global_route *grh = rdma_ah_retrieve_grh(attr);

	attr->type = RDMA_AH_ATTR_TYPE_ROCE;

	memcpy(grh->dgid.raw, av->grh.dgid.raw, sizeof(av->grh.dgid.raw));
	grh->flow_label = av->grh.flow_label;
	grh->sgid_index = av->grh.sgid_index;
	grh->hop_limit = av->grh.hop_limit;
	grh->traffic_class = av->grh.traffic_class;

	rdma_ah_set_ah_flags(attr, IB_AH_GRH);
	rdma_ah_set_port_num(attr, av->port_num);
}