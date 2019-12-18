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
struct TYPE_4__ {int mode; int mask; } ;
struct rdma_port_counter {TYPE_2__ mode; } ;
struct ib_device {TYPE_1__* port_data; } ;
typedef  enum rdma_nl_counter_mode { ____Placeholder_rdma_nl_counter_mode } rdma_nl_counter_mode ;
typedef  enum rdma_nl_counter_mask { ____Placeholder_rdma_nl_counter_mask } rdma_nl_counter_mask ;
struct TYPE_3__ {struct rdma_port_counter port_counter; } ;

/* Variables and functions */

int rdma_counter_get_mode(struct ib_device *dev, u8 port,
			  enum rdma_nl_counter_mode *mode,
			  enum rdma_nl_counter_mask *mask)
{
	struct rdma_port_counter *port_counter;

	port_counter = &dev->port_data[port].port_counter;
	*mode = port_counter->mode.mode;
	*mask = port_counter->mode.mask;

	return 0;
}