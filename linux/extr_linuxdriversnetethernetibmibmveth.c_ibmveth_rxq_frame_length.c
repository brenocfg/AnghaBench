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
struct TYPE_4__ {size_t index; TYPE_1__* queue_addr; } ;
struct ibmveth_adapter {TYPE_2__ rx_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ibmveth_rxq_frame_length(struct ibmveth_adapter *adapter)
{
	return be32_to_cpu(adapter->rx_queue.queue_addr[adapter->rx_queue.index].length);
}