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
struct rdma_counter {scalar_t__ device; scalar_t__ port; } ;
struct ib_qp {scalar_t__ device; scalar_t__ port; } ;

/* Variables and functions */
 int EINVAL ; 
 int __rdma_counter_bind_qp (struct rdma_counter*,struct ib_qp*) ; 

__attribute__((used)) static int rdma_counter_bind_qp_manual(struct rdma_counter *counter,
				       struct ib_qp *qp)
{
	if ((counter->device != qp->device) || (counter->port != qp->port))
		return -EINVAL;

	return __rdma_counter_bind_qp(counter, qp);
}