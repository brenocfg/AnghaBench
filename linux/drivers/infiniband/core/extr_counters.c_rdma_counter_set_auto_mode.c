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
typedef  size_t u8 ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct rdma_port_counter {int /*<<< orphan*/  lock; TYPE_2__ mode; scalar_t__ num_counters; int /*<<< orphan*/  hstats; } ;
struct ib_device {TYPE_1__* port_data; } ;
typedef  enum rdma_nl_counter_mask { ____Placeholder_rdma_nl_counter_mask } rdma_nl_counter_mask ;
struct TYPE_3__ {struct rdma_port_counter port_counter; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ RDMA_COUNTER_MODE_AUTO ; 
 scalar_t__ RDMA_COUNTER_MODE_MANUAL ; 
 scalar_t__ RDMA_COUNTER_MODE_NONE ; 
 int __counter_set_mode (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int rdma_counter_set_auto_mode(struct ib_device *dev, u8 port,
			       bool on, enum rdma_nl_counter_mask mask)
{
	struct rdma_port_counter *port_counter;
	int ret;

	port_counter = &dev->port_data[port].port_counter;
	if (!port_counter->hstats)
		return -EOPNOTSUPP;

	mutex_lock(&port_counter->lock);
	if (on) {
		ret = __counter_set_mode(&port_counter->mode,
					 RDMA_COUNTER_MODE_AUTO, mask);
	} else {
		if (port_counter->mode.mode != RDMA_COUNTER_MODE_AUTO) {
			ret = -EINVAL;
			goto out;
		}

		if (port_counter->num_counters)
			ret = __counter_set_mode(&port_counter->mode,
						 RDMA_COUNTER_MODE_MANUAL, 0);
		else
			ret = __counter_set_mode(&port_counter->mode,
						 RDMA_COUNTER_MODE_NONE, 0);
	}

out:
	mutex_unlock(&port_counter->lock);
	return ret;
}