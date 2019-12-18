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
typedef  int /*<<< orphan*/  u8 ;
struct rdma_ah_attr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_ibport {int /*<<< orphan*/ * sl_to_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 size_t rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

u8 ah_to_sc(struct ib_device *ibdev, struct rdma_ah_attr *ah)
{
	struct hfi1_ibport *ibp = to_iport(ibdev, rdma_ah_get_port_num(ah));

	return ibp->sl_to_sc[rdma_ah_get_sl(ah)];
}