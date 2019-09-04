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
struct ibmvnic_adapter {TYPE_2__* rx_pool; TYPE_1__* login_rsp_buf; int /*<<< orphan*/  replenish_task_cycles; } ;
struct TYPE_4__ {scalar_t__ active; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_rxadd_subcrqs; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replenish_rx_pool (struct ibmvnic_adapter*,TYPE_2__*) ; 

__attribute__((used)) static void replenish_pools(struct ibmvnic_adapter *adapter)
{
	int i;

	adapter->replenish_task_cycles++;
	for (i = 0; i < be32_to_cpu(adapter->login_rsp_buf->num_rxadd_subcrqs);
	     i++) {
		if (adapter->rx_pool[i].active)
			replenish_rx_pool(adapter, &adapter->rx_pool[i]);
	}
}