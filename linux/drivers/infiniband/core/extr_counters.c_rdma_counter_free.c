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
struct TYPE_6__ {scalar_t__ mode; } ;
struct rdma_port_counter {int /*<<< orphan*/  lock; TYPE_3__ mode; int /*<<< orphan*/  num_counters; } ;
struct rdma_counter {size_t port; struct rdma_counter* stats; int /*<<< orphan*/  res; TYPE_2__* device; } ;
struct TYPE_5__ {TYPE_1__* port_data; } ;
struct TYPE_4__ {struct rdma_port_counter port_counter; } ;

/* Variables and functions */
 scalar_t__ RDMA_COUNTER_MODE_MANUAL ; 
 int /*<<< orphan*/  RDMA_COUNTER_MODE_NONE ; 
 int /*<<< orphan*/  __counter_set_mode (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rdma_counter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rdma_counter_free(struct rdma_counter *counter)
{
	struct rdma_port_counter *port_counter;

	port_counter = &counter->device->port_data[counter->port].port_counter;
	mutex_lock(&port_counter->lock);
	port_counter->num_counters--;
	if (!port_counter->num_counters &&
	    (port_counter->mode.mode == RDMA_COUNTER_MODE_MANUAL))
		__counter_set_mode(&port_counter->mode, RDMA_COUNTER_MODE_NONE,
				   0);

	mutex_unlock(&port_counter->lock);

	rdma_restrack_del(&counter->res);
	kfree(counter->stats);
	kfree(counter);
}