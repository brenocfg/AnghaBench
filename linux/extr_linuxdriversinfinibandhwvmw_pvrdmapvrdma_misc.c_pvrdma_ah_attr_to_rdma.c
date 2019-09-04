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
struct TYPE_2__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_1__ roce; int /*<<< orphan*/  type; } ;
struct pvrdma_ah_attr {int /*<<< orphan*/  dmac; int /*<<< orphan*/  port_num; int /*<<< orphan*/  ah_flags; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; int /*<<< orphan*/  grh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_global_route_to_ib (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ah_retrieve_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_set_ah_flags (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 

void pvrdma_ah_attr_to_rdma(struct rdma_ah_attr *dst,
			    const struct pvrdma_ah_attr *src)
{
	dst->type = RDMA_AH_ATTR_TYPE_ROCE;
	pvrdma_global_route_to_ib(rdma_ah_retrieve_grh(dst), &src->grh);
	rdma_ah_set_dlid(dst, src->dlid);
	rdma_ah_set_sl(dst, src->sl);
	rdma_ah_set_path_bits(dst, src->src_path_bits);
	rdma_ah_set_static_rate(dst, src->static_rate);
	rdma_ah_set_ah_flags(dst, src->ah_flags);
	rdma_ah_set_port_num(dst, src->port_num);
	memcpy(dst->roce.dmac, &src->dmac, ETH_ALEN);
}