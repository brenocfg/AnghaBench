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
struct i40e_hw {scalar_t__ hw_addr; } ;
struct i40evf_adapter {int num_active_queues; TYPE_1__* tx_rings; struct i40e_hw hw; } ;
struct TYPE_2__ {scalar_t__ tail; } ;

/* Variables and functions */
 scalar_t__ I40E_QTX_TAIL1 (int) ; 

__attribute__((used)) static void i40evf_configure_tx(struct i40evf_adapter *adapter)
{
	struct i40e_hw *hw = &adapter->hw;
	int i;

	for (i = 0; i < adapter->num_active_queues; i++)
		adapter->tx_rings[i].tail = hw->hw_addr + I40E_QTX_TAIL1(i);
}