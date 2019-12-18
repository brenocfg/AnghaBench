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
struct rdma_counter {int /*<<< orphan*/  kref; } ;
struct ib_qp {struct rdma_counter* counter; } ;

/* Variables and functions */
 int EINVAL ; 
 int __rdma_counter_unbind_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  counter_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rdma_counter_unbind_qp(struct ib_qp *qp, bool force)
{
	struct rdma_counter *counter = qp->counter;
	int ret;

	if (!counter)
		return -EINVAL;

	ret = __rdma_counter_unbind_qp(qp);
	if (ret && !force)
		return ret;

	kref_put(&counter->kref, counter_release);
	return 0;
}