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
struct TYPE_2__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct ftgmac100 {int need_mac_restart; int /*<<< orphan*/  napi; scalar_t__ base; int /*<<< orphan*/  reset_task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int FTGMAC100_INT_AHB_ERR ; 
 unsigned int FTGMAC100_INT_BAD ; 
 unsigned int FTGMAC100_INT_NO_RXBUF ; 
 unsigned int FTGMAC100_INT_RPKT_LOST ; 
 unsigned int FTGMAC100_INT_XPKT_LOST ; 
 scalar_t__ FTGMAC100_OFFSET_IER ; 
 scalar_t__ FTGMAC100_OFFSET_ISR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static irqreturn_t ftgmac100_interrupt(int irq, void *dev_id)
{
	struct net_device *netdev = dev_id;
	struct ftgmac100 *priv = netdev_priv(netdev);
	unsigned int status, new_mask = FTGMAC100_INT_BAD;

	/* Fetch and clear interrupt bits, process abnormal ones */
	status = ioread32(priv->base + FTGMAC100_OFFSET_ISR);
	iowrite32(status, priv->base + FTGMAC100_OFFSET_ISR);
	if (unlikely(status & FTGMAC100_INT_BAD)) {

		/* RX buffer unavailable */
		if (status & FTGMAC100_INT_NO_RXBUF)
			netdev->stats.rx_over_errors++;

		/* received packet lost due to RX FIFO full */
		if (status & FTGMAC100_INT_RPKT_LOST)
			netdev->stats.rx_fifo_errors++;

		/* sent packet lost due to excessive TX collision */
		if (status & FTGMAC100_INT_XPKT_LOST)
			netdev->stats.tx_fifo_errors++;

		/* AHB error -> Reset the chip */
		if (status & FTGMAC100_INT_AHB_ERR) {
			if (net_ratelimit())
				netdev_warn(netdev,
					   "AHB bus error ! Resetting chip.\n");
			iowrite32(0, priv->base + FTGMAC100_OFFSET_IER);
			schedule_work(&priv->reset_task);
			return IRQ_HANDLED;
		}

		/* We may need to restart the MAC after such errors, delay
		 * this until after we have freed some Rx buffers though
		 */
		priv->need_mac_restart = true;

		/* Disable those errors until we restart */
		new_mask &= ~status;
	}

	/* Only enable "bad" interrupts while NAPI is on */
	iowrite32(new_mask, priv->base + FTGMAC100_OFFSET_IER);

	/* Schedule NAPI bh */
	napi_schedule_irqoff(&priv->napi);

	return IRQ_HANDLED;
}