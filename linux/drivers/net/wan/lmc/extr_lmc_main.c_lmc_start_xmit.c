#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {int /*<<< orphan*/  tx_NoCompleteCnt; int /*<<< orphan*/  tx_tbusy1; } ;
struct TYPE_8__ {int lmc_next_tx; int lmc_taint_tx; int lmc_txfull; int TxDescriptControlInit; int /*<<< orphan*/  lmc_lock; TYPE_2__* lmc_txring; TYPE_1__ extra_stats; struct sk_buff** lmc_txq; } ;
typedef  TYPE_3__ lmc_softc_t ;
struct TYPE_7__ {int length; int status; int /*<<< orphan*/  buffer1; } ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CONSOLE_LOG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMC_EVENT_LOG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LMC_EVENT_TBUSY1 ; 
 int /*<<< orphan*/  LMC_EVENT_XMT ; 
 int LMC_TDES_END_OF_RING ; 
 int LMC_TDES_INTERRUPT_ON_COMPLETION ; 
 int LMC_TXDESCS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  csr_txpoll ; 
 TYPE_3__* dev_to_sc (struct net_device*) ; 
 int /*<<< orphan*/  lmc_trace (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t lmc_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 flag;
    int entry;
    unsigned long flags;

    lmc_trace(dev, "lmc_start_xmit in");

    spin_lock_irqsave(&sc->lmc_lock, flags);

    /* normal path, tbusy known to be zero */

    entry = sc->lmc_next_tx % LMC_TXDESCS;

    sc->lmc_txq[entry] = skb;
    sc->lmc_txring[entry].buffer1 = virt_to_bus (skb->data);

    LMC_CONSOLE_LOG("xmit", skb->data, skb->len);

#ifndef GCOM
    /* If the queue is less than half full, don't interrupt */
    if (sc->lmc_next_tx - sc->lmc_taint_tx < LMC_TXDESCS / 2)
    {
        /* Do not interrupt on completion of this packet */
        flag = 0x60000000;
        netif_wake_queue(dev);
    }
    else if (sc->lmc_next_tx - sc->lmc_taint_tx == LMC_TXDESCS / 2)
    {
        /* This generates an interrupt on completion of this packet */
        flag = 0xe0000000;
        netif_wake_queue(dev);
    }
    else if (sc->lmc_next_tx - sc->lmc_taint_tx < LMC_TXDESCS - 1)
    {
        /* Do not interrupt on completion of this packet */
        flag = 0x60000000;
        netif_wake_queue(dev);
    }
    else
    {
        /* This generates an interrupt on completion of this packet */
        flag = 0xe0000000;
        sc->lmc_txfull = 1;
        netif_stop_queue(dev);
    }
#else
    flag = LMC_TDES_INTERRUPT_ON_COMPLETION;

    if (sc->lmc_next_tx - sc->lmc_taint_tx >= LMC_TXDESCS - 1)
    {				/* ring full, go busy */
        sc->lmc_txfull = 1;
	netif_stop_queue(dev);
	sc->extra_stats.tx_tbusy1++;
        LMC_EVENT_LOG(LMC_EVENT_TBUSY1, entry, 0);
    }
#endif


    if (entry == LMC_TXDESCS - 1)	/* last descriptor in ring */
	flag |= LMC_TDES_END_OF_RING;	/* flag as such for Tulip */

    /* don't pad small packets either */
    flag = sc->lmc_txring[entry].length = (skb->len) | flag |
						sc->TxDescriptControlInit;

    /* set the transmit timeout flag to be checked in
     * the watchdog timer handler. -baz
     */

    sc->extra_stats.tx_NoCompleteCnt++;
    sc->lmc_next_tx++;

    /* give ownership to the chip */
    LMC_EVENT_LOG(LMC_EVENT_XMT, flag, entry);
    sc->lmc_txring[entry].status = 0x80000000;

    /* send now! */
    LMC_CSR_WRITE (sc, csr_txpoll, 0);

    spin_unlock_irqrestore(&sc->lmc_lock, flags);

    lmc_trace(dev, "lmc_start_xmit_out");
    return NETDEV_TX_OK;
}