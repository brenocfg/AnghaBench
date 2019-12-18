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
struct rdma_counter {int /*<<< orphan*/  lock; struct ib_device* device; } ;
struct TYPE_2__ {int (* counter_update_stats ) (struct rdma_counter*) ;} ;
struct ib_device {TYPE_1__ ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rdma_counter*) ; 

int rdma_counter_query_stats(struct rdma_counter *counter)
{
	struct ib_device *dev = counter->device;
	int ret;

	if (!dev->ops.counter_update_stats)
		return -EINVAL;

	mutex_lock(&counter->lock);
	ret = dev->ops.counter_update_stats(counter);
	mutex_unlock(&counter->lock);

	return ret;
}