#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct de_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; int /*<<< orphan*/  rx_tail; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IntrErr ; 
 int IntrOK ; 
 int LinkFail ; 
 int LinkPass ; 
 int /*<<< orphan*/  MacMode ; 
 int /*<<< orphan*/  MacStatus ; 
 int NormalRxPoll ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PciErr ; 
 int RxEmpty ; 
 int RxIntr ; 
 int /*<<< orphan*/  RxPoll ; 
 int TxEmpty ; 
 int TxIntr ; 
 int /*<<< orphan*/  de_media_interrupt (struct de_private*,int) ; 
 int /*<<< orphan*/  de_rx (struct de_private*) ; 
 int /*<<< orphan*/  de_tx (struct de_private*) ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct de_private*,int /*<<< orphan*/ ,struct net_device*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t de_interrupt (int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct de_private *de = netdev_priv(dev);
	u32 status;

	status = dr32(MacStatus);
	if ((!(status & (IntrOK|IntrErr))) || (status == 0xFFFF))
		return IRQ_NONE;

	netif_dbg(de, intr, dev, "intr, status %08x mode %08x desc %u/%u/%u\n",
		  status, dr32(MacMode),
		  de->rx_tail, de->tx_head, de->tx_tail);

	dw32(MacStatus, status);

	if (status & (RxIntr | RxEmpty)) {
		de_rx(de);
		if (status & RxEmpty)
			dw32(RxPoll, NormalRxPoll);
	}

	spin_lock(&de->lock);

	if (status & (TxIntr | TxEmpty))
		de_tx(de);

	if (status & (LinkPass | LinkFail))
		de_media_interrupt(de, status);

	spin_unlock(&de->lock);

	if (status & PciErr) {
		u16 pci_status;

		pci_read_config_word(de->pdev, PCI_STATUS, &pci_status);
		pci_write_config_word(de->pdev, PCI_STATUS, pci_status);
		netdev_err(de->dev,
			   "PCI bus error, status=%08x, PCI status=%04x\n",
			   status, pci_status);
	}

	return IRQ_HANDLED;
}