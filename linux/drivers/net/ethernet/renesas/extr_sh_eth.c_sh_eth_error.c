#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_eth_private {TYPE_2__* cd; int /*<<< orphan*/  dirty_tx; int /*<<< orphan*/  cur_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {scalar_t__ state; TYPE_1__ stats; } ;
struct TYPE_4__ {int edtrr_trns; scalar_t__ no_ade; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDTRR ; 
 int EESR_ADE ; 
 int EESR_RABT ; 
 int EESR_RDE ; 
 int EESR_RFE ; 
 int EESR_RFRMER ; 
 int EESR_TABT ; 
 int EESR_TDE ; 
 int EESR_TFE ; 
 int EESR_TWB ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct sh_eth_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int sh_eth_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_tx_free (struct net_device*,int) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void sh_eth_error(struct net_device *ndev, u32 intr_status)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u32 mask;

	if (intr_status & EESR_TWB) {
		/* Unused write back interrupt */
		if (intr_status & EESR_TABT) {	/* Transmit Abort int */
			ndev->stats.tx_aborted_errors++;
			netif_err(mdp, tx_err, ndev, "Transmit Abort\n");
		}
	}

	if (intr_status & EESR_RABT) {
		/* Receive Abort int */
		if (intr_status & EESR_RFRMER) {
			/* Receive Frame Overflow int */
			ndev->stats.rx_frame_errors++;
		}
	}

	if (intr_status & EESR_TDE) {
		/* Transmit Descriptor Empty int */
		ndev->stats.tx_fifo_errors++;
		netif_err(mdp, tx_err, ndev, "Transmit Descriptor Empty\n");
	}

	if (intr_status & EESR_TFE) {
		/* FIFO under flow */
		ndev->stats.tx_fifo_errors++;
		netif_err(mdp, tx_err, ndev, "Transmit FIFO Under flow\n");
	}

	if (intr_status & EESR_RDE) {
		/* Receive Descriptor Empty int */
		ndev->stats.rx_over_errors++;
	}

	if (intr_status & EESR_RFE) {
		/* Receive FIFO Overflow int */
		ndev->stats.rx_fifo_errors++;
	}

	if (!mdp->cd->no_ade && (intr_status & EESR_ADE)) {
		/* Address Error */
		ndev->stats.tx_fifo_errors++;
		netif_err(mdp, tx_err, ndev, "Address Error\n");
	}

	mask = EESR_TWB | EESR_TABT | EESR_ADE | EESR_TDE | EESR_TFE;
	if (mdp->cd->no_ade)
		mask &= ~EESR_ADE;
	if (intr_status & mask) {
		/* Tx error */
		u32 edtrr = sh_eth_read(ndev, EDTRR);

		/* dmesg */
		netdev_err(ndev, "TX error. status=%8.8x cur_tx=%8.8x dirty_tx=%8.8x state=%8.8x EDTRR=%8.8x.\n",
			   intr_status, mdp->cur_tx, mdp->dirty_tx,
			   (u32)ndev->state, edtrr);
		/* dirty buffer free */
		sh_eth_tx_free(ndev, true);

		/* SH7712 BUG */
		if (edtrr ^ mdp->cd->edtrr_trns) {
			/* tx dma start */
			sh_eth_write(ndev, mdp->cd->edtrr_trns, EDTRR);
		}
		/* wakeup */
		netif_wake_queue(ndev);
	}
}