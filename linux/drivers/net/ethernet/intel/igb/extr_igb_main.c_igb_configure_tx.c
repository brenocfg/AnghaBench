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
struct e1000_hw {int dummy; } ;
struct igb_adapter {int num_tx_queues; TYPE_1__** tx_ring; struct e1000_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_configure_tx_ring (struct igb_adapter*,TYPE_1__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igb_configure_tx(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	int i;

	/* disable the queues */
	for (i = 0; i < adapter->num_tx_queues; i++)
		wr32(E1000_TXDCTL(adapter->tx_ring[i]->reg_idx), 0);

	wrfl();
	usleep_range(10000, 20000);

	for (i = 0; i < adapter->num_tx_queues; i++)
		igb_configure_tx_ring(adapter, adapter->tx_ring[i]);
}