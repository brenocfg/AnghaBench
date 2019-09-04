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
struct rdma_ah_attr {TYPE_1__ roce; } ;
struct pvrdma_ah_attr {int /*<<< orphan*/  dmac; int /*<<< orphan*/  port_num; int /*<<< orphan*/  ah_flags; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; int /*<<< orphan*/  grh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_global_route_to_pvrdma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_get_ah_flags (struct rdma_ah_attr const*) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (struct rdma_ah_attr const*) ; 
 int /*<<< orphan*/  rdma_ah_get_path_bits (struct rdma_ah_attr const*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr const*) ; 
 int /*<<< orphan*/  rdma_ah_get_sl (struct rdma_ah_attr const*) ; 
 int /*<<< orphan*/  rdma_ah_get_static_rate (struct rdma_ah_attr const*) ; 
 int /*<<< orphan*/  rdma_ah_read_grh (struct rdma_ah_attr const*) ; 

void rdma_ah_attr_to_pvrdma(struct pvrdma_ah_attr *dst,
			    const struct rdma_ah_attr *src)
{
	ib_global_route_to_pvrdma(&dst->grh, rdma_ah_read_grh(src));
	dst->dlid = rdma_ah_get_dlid(src);
	dst->sl = rdma_ah_get_sl(src);
	dst->src_path_bits = rdma_ah_get_path_bits(src);
	dst->static_rate = rdma_ah_get_static_rate(src);
	dst->ah_flags = rdma_ah_get_ah_flags(src);
	dst->port_num = rdma_ah_get_port_num(src);
	memcpy(&dst->dmac, src->roce.dmac, sizeof(dst->dmac));
}