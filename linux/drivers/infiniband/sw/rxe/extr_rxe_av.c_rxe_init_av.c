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
struct rxe_av {int /*<<< orphan*/  dmac; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_1__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rxe_av_fill_ip_info (struct rxe_av*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rxe_av_from_attr (int /*<<< orphan*/ ,struct rxe_av*,struct rdma_ah_attr*) ; 

void rxe_init_av(struct rdma_ah_attr *attr, struct rxe_av *av)
{
	rxe_av_from_attr(rdma_ah_get_port_num(attr), av, attr);
	rxe_av_fill_ip_info(av, attr);
	memcpy(av->dmac, attr->roce.dmac, ETH_ALEN);
}