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
struct vmxnet3_adapter {int num_rx_queues; int /*<<< orphan*/  netdev; scalar_t__ link_speed; TYPE_1__* rx_queue; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_QUIESCE_DEV ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_STATE_BIT_QUIESCED ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmxnet3_disable_all_intrs (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_free_irqs (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_rq_cleanup_all (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_tq_cleanup_all (struct vmxnet3_adapter*) ; 

int
vmxnet3_quiesce_dev(struct vmxnet3_adapter *adapter)
{
	int i;
	unsigned long flags;
	if (test_and_set_bit(VMXNET3_STATE_BIT_QUIESCED, &adapter->state))
		return 0;


	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_QUIESCE_DEV);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	vmxnet3_disable_all_intrs(adapter);

	for (i = 0; i < adapter->num_rx_queues; i++)
		napi_disable(&adapter->rx_queue[i].napi);
	netif_tx_disable(adapter->netdev);
	adapter->link_speed = 0;
	netif_carrier_off(adapter->netdev);

	vmxnet3_tq_cleanup_all(adapter);
	vmxnet3_rq_cleanup_all(adapter);
	vmxnet3_free_irqs(adapter);
	return 0;
}