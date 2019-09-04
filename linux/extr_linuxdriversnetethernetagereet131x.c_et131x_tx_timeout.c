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
struct tx_ring {struct tcb* send_head; } ;
struct tcb {scalar_t__ count; int /*<<< orphan*/  index; } ;
struct net_device {int dummy; } ;
struct et131x_adapter {int flags; TYPE_3__* netdev; TYPE_1__* pdev; int /*<<< orphan*/  tcb_send_qlock; struct tx_ring tx_ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FMP_ADAPTER_HARDWARE_ERROR ; 
 int FMP_ADAPTER_INTERRUPT_IN_USE ; 
 int FMP_ADAPTER_NON_RECOVER_ERROR ; 
 scalar_t__ NIC_SEND_HANG_THRESHOLD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et131x_disable_txrx (struct net_device*) ; 
 int /*<<< orphan*/  et131x_enable_txrx (struct net_device*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void et131x_tx_timeout(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	struct tx_ring *tx_ring = &adapter->tx_ring;
	struct tcb *tcb;
	unsigned long flags;

	/* If the device is closed, ignore the timeout */
	if (!(adapter->flags & FMP_ADAPTER_INTERRUPT_IN_USE))
		return;

	/* Any nonrecoverable hardware error?
	 * Checks adapter->flags for any failure in phy reading
	 */
	if (adapter->flags & FMP_ADAPTER_NON_RECOVER_ERROR)
		return;

	/* Hardware failure? */
	if (adapter->flags & FMP_ADAPTER_HARDWARE_ERROR) {
		dev_err(&adapter->pdev->dev, "hardware error - reset\n");
		return;
	}

	/* Is send stuck? */
	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);
	tcb = tx_ring->send_head;
	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

	if (tcb) {
		tcb->count++;

		if (tcb->count > NIC_SEND_HANG_THRESHOLD) {
			dev_warn(&adapter->pdev->dev,
				 "Send stuck - reset. tcb->WrIndex %x\n",
				 tcb->index);

			adapter->netdev->stats.tx_errors++;

			/* perform reset of tx/rx */
			et131x_disable_txrx(netdev);
			et131x_enable_txrx(netdev);
		}
	}
}