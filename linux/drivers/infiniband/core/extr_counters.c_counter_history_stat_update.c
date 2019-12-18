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
struct rdma_port_counter {TYPE_3__* hstats; } ;
struct rdma_counter {size_t port; TYPE_1__* stats; struct ib_device* device; } ;
struct ib_device {TYPE_2__* port_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {struct rdma_port_counter port_counter; } ;
struct TYPE_4__ {int num_counters; scalar_t__* value; } ;

/* Variables and functions */

__attribute__((used)) static void counter_history_stat_update(const struct rdma_counter *counter)
{
	struct ib_device *dev = counter->device;
	struct rdma_port_counter *port_counter;
	int i;

	port_counter = &dev->port_data[counter->port].port_counter;
	if (!port_counter->hstats)
		return;

	for (i = 0; i < counter->stats->num_counters; i++)
		port_counter->hstats->value[i] += counter->stats->value[i];
}