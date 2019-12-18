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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  reset_task_pending; int /*<<< orphan*/  reset_task_pending_all; int /*<<< orphan*/ * stat_lock; TYPE_1__* net_stats; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_RESET_ALL ; 
 int INTR_MAC_CTRL_STATUS ; 
 int INTR_MIF_STATUS ; 
 int INTR_PCI_ERROR_STATUS ; 
 int INTR_PCS_STATUS ; 
 int INTR_RX_LEN_MISMATCH ; 
 int INTR_RX_MAC_STATUS ; 
 int INTR_RX_TAG_ERROR ; 
 int INTR_TX_MAC_STATUS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cas_mac_interrupt (struct net_device*,struct cas*,int) ; 
 scalar_t__ cas_mif_interrupt (struct net_device*,struct cas*,int) ; 
 scalar_t__ cas_pci_interrupt (struct net_device*,struct cas*,int) ; 
 scalar_t__ cas_pcs_interrupt (struct net_device*,struct cas*,int) ; 
 scalar_t__ cas_rxmac_interrupt (struct net_device*,struct cas*,int) ; 
 scalar_t__ cas_txmac_interrupt (struct net_device*,struct cas*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cas_abnormal_irq(struct net_device *dev, struct cas *cp,
			    u32 status)
{
	if (status & INTR_RX_TAG_ERROR) {
		/* corrupt RX tag framing */
		netif_printk(cp, rx_err, KERN_DEBUG, cp->dev,
			     "corrupt rx tag framing\n");
		spin_lock(&cp->stat_lock[0]);
		cp->net_stats[0].rx_errors++;
		spin_unlock(&cp->stat_lock[0]);
		goto do_reset;
	}

	if (status & INTR_RX_LEN_MISMATCH) {
		/* length mismatch. */
		netif_printk(cp, rx_err, KERN_DEBUG, cp->dev,
			     "length mismatch for rx frame\n");
		spin_lock(&cp->stat_lock[0]);
		cp->net_stats[0].rx_errors++;
		spin_unlock(&cp->stat_lock[0]);
		goto do_reset;
	}

	if (status & INTR_PCS_STATUS) {
		if (cas_pcs_interrupt(dev, cp, status))
			goto do_reset;
	}

	if (status & INTR_TX_MAC_STATUS) {
		if (cas_txmac_interrupt(dev, cp, status))
			goto do_reset;
	}

	if (status & INTR_RX_MAC_STATUS) {
		if (cas_rxmac_interrupt(dev, cp, status))
			goto do_reset;
	}

	if (status & INTR_MAC_CTRL_STATUS) {
		if (cas_mac_interrupt(dev, cp, status))
			goto do_reset;
	}

	if (status & INTR_MIF_STATUS) {
		if (cas_mif_interrupt(dev, cp, status))
			goto do_reset;
	}

	if (status & INTR_PCI_ERROR_STATUS) {
		if (cas_pci_interrupt(dev, cp, status))
			goto do_reset;
	}
	return 0;

do_reset:
#if 1
	atomic_inc(&cp->reset_task_pending);
	atomic_inc(&cp->reset_task_pending_all);
	netdev_err(dev, "reset called in cas_abnormal_irq [0x%x]\n", status);
	schedule_work(&cp->reset_task);
#else
	atomic_set(&cp->reset_task_pending, CAS_RESET_ALL);
	netdev_err(dev, "reset called in cas_abnormal_irq\n");
	schedule_work(&cp->reset_task);
#endif
	return 1;
}