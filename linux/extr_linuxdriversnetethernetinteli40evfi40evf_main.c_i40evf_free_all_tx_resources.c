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
struct i40evf_adapter {int num_active_queues; TYPE_1__* tx_rings; } ;
struct TYPE_2__ {scalar_t__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40evf_free_tx_resources (TYPE_1__*) ; 

void i40evf_free_all_tx_resources(struct i40evf_adapter *adapter)
{
	int i;

	if (!adapter->tx_rings)
		return;

	for (i = 0; i < adapter->num_active_queues; i++)
		if (adapter->tx_rings[i].desc)
			i40evf_free_tx_resources(&adapter->tx_rings[i]);
}