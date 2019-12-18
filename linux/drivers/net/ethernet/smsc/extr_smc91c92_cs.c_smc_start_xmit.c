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
typedef  int u_short ;
struct smc_private {int /*<<< orphan*/  lock; scalar_t__ rx_ovrn; int /*<<< orphan*/  packets_waiting; struct sk_buff* saved_skb; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 short IM_ALLOC_INT ; 
 unsigned int INTERRUPT ; 
 int MC_ALLOC ; 
 short MC_RESET ; 
 short MEMORY_WAIT_TIME ; 
 unsigned int MMU_CMD ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 short inw (unsigned int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (short,unsigned int) ; 
 int /*<<< orphan*/  smc_hardware_send_packet (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t smc_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
    struct smc_private *smc = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    u_short num_pages;
    short time_out, ir;
    unsigned long flags;

    netif_stop_queue(dev);

    netdev_dbg(dev, "smc_start_xmit(length = %d) called, status %04x\n",
	       skb->len, inw(ioaddr + 2));

    if (smc->saved_skb) {
	/* THIS SHOULD NEVER HAPPEN. */
	dev->stats.tx_aborted_errors++;
	netdev_dbg(dev, "Internal error -- sent packet while busy\n");
	return NETDEV_TX_BUSY;
    }
    smc->saved_skb = skb;

    num_pages = skb->len >> 8;

    if (num_pages > 7) {
	netdev_err(dev, "Far too big packet error: %d pages\n", num_pages);
	dev_kfree_skb (skb);
	smc->saved_skb = NULL;
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;		/* Do not re-queue this packet. */
    }
    /* A packet is now waiting. */
    smc->packets_waiting++;

    spin_lock_irqsave(&smc->lock, flags);
    SMC_SELECT_BANK(2);	/* Paranoia, we should always be in window 2 */

    /* need MC_RESET to keep the memory consistent. errata? */
    if (smc->rx_ovrn) {
	outw(MC_RESET, ioaddr + MMU_CMD);
	smc->rx_ovrn = 0;
    }

    /* Allocate the memory; send the packet now if we win. */
    outw(MC_ALLOC | num_pages, ioaddr + MMU_CMD);
    for (time_out = MEMORY_WAIT_TIME; time_out >= 0; time_out--) {
	ir = inw(ioaddr+INTERRUPT);
	if (ir & IM_ALLOC_INT) {
	    /* Acknowledge the interrupt, send the packet. */
	    outw((ir&0xff00) | IM_ALLOC_INT, ioaddr + INTERRUPT);
	    smc_hardware_send_packet(dev);	/* Send the packet now.. */
	    spin_unlock_irqrestore(&smc->lock, flags);
	    return NETDEV_TX_OK;
	}
    }

    /* Otherwise defer until the Tx-space-allocated interrupt. */
    netdev_dbg(dev, "memory allocation deferred.\n");
    outw((IM_ALLOC_INT << 8) | (ir & 0xff00), ioaddr + INTERRUPT);
    spin_unlock_irqrestore(&smc->lock, flags);

    return NETDEV_TX_OK;
}