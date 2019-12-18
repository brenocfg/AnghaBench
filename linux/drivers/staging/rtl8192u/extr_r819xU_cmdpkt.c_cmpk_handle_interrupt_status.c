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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  txbeaconerr; int /*<<< orphan*/  txbeaconokint; } ;
struct r8192_priv {TYPE_2__ stats; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct cmd_pkt_interrupt_status {int length; int interrupt_status; } ;
struct TYPE_3__ {scalar_t__ iw_mode; int bibsscoordinator; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*,...) ; 
 int ISR_BCN_TIMER_INTR ; 
 int ISR_TX_BCN_ERR ; 
 int ISR_TX_BCN_OK ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int /*<<< orphan*/  cmdpkt_beacontimerinterrupt_819xusb (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void cmpk_handle_interrupt_status(struct net_device *dev, u8 *pmsg)
{
	struct cmd_pkt_interrupt_status	 rx_intr_status;	/* */
	struct r8192_priv *priv = ieee80211_priv(dev);

	DMESG("---> cmpk_Handle_Interrupt_Status()\n");

	/* 1. Extract TX feedback info from RFD to temp structure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	 * windows OS. So we have to read the content byte by byte or transfer
	 * endian type before copy the message copy.
	 */
	rx_intr_status.length = pmsg[1];
	if (rx_intr_status.length != (sizeof(struct cmd_pkt_interrupt_status) - 2)) {
		DMESG("cmpk_Handle_Interrupt_Status: wrong length!\n");
		return;
	}

	/* Statistics of beacon for ad-hoc mode. */
	if (priv->ieee80211->iw_mode == IW_MODE_ADHOC) {
		/* 2 maybe need endian transform? */
		rx_intr_status.interrupt_status = *((u32 *)(pmsg + 4));

		DMESG("interrupt status = 0x%x\n",
		      rx_intr_status.interrupt_status);

		if (rx_intr_status.interrupt_status & ISR_TX_BCN_OK) {
			priv->ieee80211->bibsscoordinator = true;
			priv->stats.txbeaconokint++;
		} else if (rx_intr_status.interrupt_status & ISR_TX_BCN_ERR) {
			priv->ieee80211->bibsscoordinator = false;
			priv->stats.txbeaconerr++;
		}

		if (rx_intr_status.interrupt_status & ISR_BCN_TIMER_INTR)
			cmdpkt_beacontimerinterrupt_819xusb(dev);
	}

	/* Other information in interrupt status we need? */

	DMESG("<---- cmpk_handle_interrupt_status()\n");
}