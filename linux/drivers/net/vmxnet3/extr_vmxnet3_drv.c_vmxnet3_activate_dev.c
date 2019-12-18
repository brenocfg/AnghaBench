#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vmxnet3_adapter {int num_rx_queues; int /*<<< orphan*/  state; TYPE_4__* rx_queue; TYPE_5__* netdev; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  shared_pa; TYPE_2__* tx_queue; int /*<<< orphan*/  rx_buf_per_pkt; int /*<<< orphan*/  skb_buf_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  napi; TYPE_3__* rx_ring; } ;
struct TYPE_10__ {int /*<<< orphan*/  next2fill; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_9__ {TYPE_1__ tx_ring; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VMXNET3_CMD_ACTIVATE_DEV ; 
 int /*<<< orphan*/  VMXNET3_GET_ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMXNET3_GET_ADDR_LO (int /*<<< orphan*/ ) ; 
 int VMXNET3_READ_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ) ; 
 int VMXNET3_REG_ALIGN ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_REG_DSAH ; 
 int /*<<< orphan*/  VMXNET3_REG_DSAL ; 
 scalar_t__ VMXNET3_REG_RXPROD ; 
 scalar_t__ VMXNET3_REG_RXPROD2 ; 
 int /*<<< orphan*/  VMXNET3_STATE_BIT_QUIESCED ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR0_REG (struct vmxnet3_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vmxnet3_check_link (struct vmxnet3_adapter*,int) ; 
 int /*<<< orphan*/  vmxnet3_enable_all_intrs (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_free_irqs (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_init_coalesce (struct vmxnet3_adapter*) ; 
 int vmxnet3_request_irqs (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_rq_cleanup_all (struct vmxnet3_adapter*) ; 
 int vmxnet3_rq_init_all (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_set_mc (TYPE_5__*) ; 
 int /*<<< orphan*/  vmxnet3_setup_driver_shared (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_tq_init_all (struct vmxnet3_adapter*) ; 

int
vmxnet3_activate_dev(struct vmxnet3_adapter *adapter)
{
	int err, i;
	u32 ret;
	unsigned long flags;

	netdev_dbg(adapter->netdev, "%s: skb_buf_size %d, rx_buf_per_pkt %d,"
		" ring sizes %u %u %u\n", adapter->netdev->name,
		adapter->skb_buf_size, adapter->rx_buf_per_pkt,
		adapter->tx_queue[0].tx_ring.size,
		adapter->rx_queue[0].rx_ring[0].size,
		adapter->rx_queue[0].rx_ring[1].size);

	vmxnet3_tq_init_all(adapter);
	err = vmxnet3_rq_init_all(adapter);
	if (err) {
		netdev_err(adapter->netdev,
			   "Failed to init rx queue error %d\n", err);
		goto rq_err;
	}

	err = vmxnet3_request_irqs(adapter);
	if (err) {
		netdev_err(adapter->netdev,
			   "Failed to setup irq for error %d\n", err);
		goto irq_err;
	}

	vmxnet3_setup_driver_shared(adapter);

	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAL, VMXNET3_GET_ADDR_LO(
			       adapter->shared_pa));
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAH, VMXNET3_GET_ADDR_HI(
			       adapter->shared_pa));
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_ACTIVATE_DEV);
	ret = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	if (ret != 0) {
		netdev_err(adapter->netdev,
			   "Failed to activate dev: error %u\n", ret);
		err = -EINVAL;
		goto activate_err;
	}

	vmxnet3_init_coalesce(adapter);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		VMXNET3_WRITE_BAR0_REG(adapter,
				VMXNET3_REG_RXPROD + i * VMXNET3_REG_ALIGN,
				adapter->rx_queue[i].rx_ring[0].next2fill);
		VMXNET3_WRITE_BAR0_REG(adapter, (VMXNET3_REG_RXPROD2 +
				(i * VMXNET3_REG_ALIGN)),
				adapter->rx_queue[i].rx_ring[1].next2fill);
	}

	/* Apply the rx filter settins last. */
	vmxnet3_set_mc(adapter->netdev);

	/*
	 * Check link state when first activating device. It will start the
	 * tx queue if the link is up.
	 */
	vmxnet3_check_link(adapter, true);
	for (i = 0; i < adapter->num_rx_queues; i++)
		napi_enable(&adapter->rx_queue[i].napi);
	vmxnet3_enable_all_intrs(adapter);
	clear_bit(VMXNET3_STATE_BIT_QUIESCED, &adapter->state);
	return 0;

activate_err:
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAL, 0);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAH, 0);
	vmxnet3_free_irqs(adapter);
irq_err:
rq_err:
	/* free up buffers we allocated */
	vmxnet3_rq_cleanup_all(adapter);
	return err;
}