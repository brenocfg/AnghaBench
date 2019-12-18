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
struct pciefd_rx_dma {int /*<<< orphan*/  msg; int /*<<< orphan*/  irq_status; } ;
struct TYPE_4__ {int /*<<< orphan*/ * echo_skb; } ;
struct TYPE_5__ {size_t echo_idx; int /*<<< orphan*/  echo_lock; int /*<<< orphan*/  ndev; TYPE_1__ can; } ;
struct pciefd_can {scalar_t__ irq_tag; TYPE_2__ ucan; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_pages_free; int /*<<< orphan*/  irq_status; TYPE_3__* board; struct pciefd_rx_dma* rx_dma_vaddr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PCIEFD_REG_SYS_VER1 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_msi_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_can_ack_rx_dma (struct pciefd_can*) ; 
 scalar_t__ pciefd_irq_is_lnk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_irq_rx_cnt (int /*<<< orphan*/ ) ; 
 scalar_t__ pciefd_irq_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_sys_readreg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_canfd_handle_msgs_list (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t pciefd_irq_handler(int irq, void *arg)
{
	struct pciefd_can *priv = arg;
	struct pciefd_rx_dma *rx_dma = priv->rx_dma_vaddr;

	/* INTA mode only to sync with PCIe transaction */
	if (!pci_dev_msi_enabled(priv->board->pci_dev))
		(void)pciefd_sys_readreg(priv->board, PCIEFD_REG_SYS_VER1);

	/* read IRQ status from the first 32-bits of the Rx DMA area */
	priv->irq_status = le32_to_cpu(rx_dma->irq_status);

	/* check if this (shared) IRQ is for this CAN */
	if (pciefd_irq_tag(priv->irq_status) != priv->irq_tag)
		return IRQ_NONE;

	/* handle rx messages (if any) */
	peak_canfd_handle_msgs_list(&priv->ucan,
				    rx_dma->msg,
				    pciefd_irq_rx_cnt(priv->irq_status));

	/* handle tx link interrupt (if any) */
	if (pciefd_irq_is_lnk(priv->irq_status)) {
		unsigned long flags;

		spin_lock_irqsave(&priv->tx_lock, flags);
		priv->tx_pages_free++;
		spin_unlock_irqrestore(&priv->tx_lock, flags);

		/* wake producer up (only if enough room in echo_skb array) */
		spin_lock_irqsave(&priv->ucan.echo_lock, flags);
		if (!priv->ucan.can.echo_skb[priv->ucan.echo_idx])
			netif_wake_queue(priv->ucan.ndev);

		spin_unlock_irqrestore(&priv->ucan.echo_lock, flags);
	}

	/* re-enable Rx DMA transfer for this CAN */
	pciefd_can_ack_rx_dma(priv);

	return IRQ_HANDLED;
}