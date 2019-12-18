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
struct rdma_counter {int /*<<< orphan*/  lock; } ;
struct ib_qp {TYPE_2__* device; scalar_t__ counter; } ;
struct TYPE_3__ {int (* counter_bind_qp ) (struct rdma_counter*,struct ib_qp*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rdma_counter*,struct ib_qp*) ; 

__attribute__((used)) static int __rdma_counter_bind_qp(struct rdma_counter *counter,
				  struct ib_qp *qp)
{
	int ret;

	if (qp->counter)
		return -EINVAL;

	if (!qp->device->ops.counter_bind_qp)
		return -EOPNOTSUPP;

	mutex_lock(&counter->lock);
	ret = qp->device->ops.counter_bind_qp(counter, qp);
	mutex_unlock(&counter->lock);

	return ret;
}