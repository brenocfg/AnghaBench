#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct TYPE_13__ {int /*<<< orphan*/  tx_tbusy0; int /*<<< orphan*/  tx_tbusy1; } ;
struct TYPE_14__ {int got_irq; TYPE_4__ extra_stats; struct sk_buff** lmc_txq; struct sk_buff** lmc_rxq; TYPE_3__* lmc_rxring; TYPE_2__* lmc_device; } ;
typedef  TYPE_5__ lmc_softc_t ;
struct TYPE_12__ {int buffer1; scalar_t__ length; scalar_t__ status; } ;
struct TYPE_10__ {int rx_missed_errors; } ;
struct TYPE_11__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int LMC_CSR_READ (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int LMC_DEC_SR ; 
 int LMC_DEC_ST ; 
 int /*<<< orphan*/  LMC_MII16_LED_ALL ; 
 int LMC_RXDESCS ; 
 int LMC_TXDESCS ; 
 int /*<<< orphan*/  csr_command ; 
 int /*<<< orphan*/  csr_intr ; 
 int /*<<< orphan*/  csr_missed_frames ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 TYPE_5__* dev_to_sc (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  lmc_led_off (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmc_trace (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static int lmc_ifdown (struct net_device *dev) /*fold00*/
{
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 csr6;
    int i;

    lmc_trace(dev, "lmc_ifdown in");

    /* Don't let anything else go on right now */
    //    dev->start = 0;
    netif_stop_queue(dev);
    sc->extra_stats.tx_tbusy1++;

    /* stop interrupts */
    /* Clear the interrupt mask */
    LMC_CSR_WRITE (sc, csr_intr, 0x00000000);

    /* Stop Tx and Rx on the chip */
    csr6 = LMC_CSR_READ (sc, csr_command);
    csr6 &= ~LMC_DEC_ST;		/* Turn off the Transmission bit */
    csr6 &= ~LMC_DEC_SR;		/* Turn off the Receive bit */
    LMC_CSR_WRITE (sc, csr_command, csr6);

    sc->lmc_device->stats.rx_missed_errors +=
	    LMC_CSR_READ(sc, csr_missed_frames) & 0xffff;

    /* release the interrupt */
    if(sc->got_irq == 1){
        free_irq (dev->irq, dev);
        sc->got_irq = 0;
    }

    /* free skbuffs in the Rx queue */
    for (i = 0; i < LMC_RXDESCS; i++)
    {
        struct sk_buff *skb = sc->lmc_rxq[i];
        sc->lmc_rxq[i] = NULL;
        sc->lmc_rxring[i].status = 0;
        sc->lmc_rxring[i].length = 0;
        sc->lmc_rxring[i].buffer1 = 0xDEADBEEF;
        if (skb != NULL)
            dev_kfree_skb(skb);
        sc->lmc_rxq[i] = NULL;
    }

    for (i = 0; i < LMC_TXDESCS; i++)
    {
        if (sc->lmc_txq[i] != NULL)
            dev_kfree_skb(sc->lmc_txq[i]);
        sc->lmc_txq[i] = NULL;
    }

    lmc_led_off (sc, LMC_MII16_LED_ALL);

    netif_wake_queue(dev);
    sc->extra_stats.tx_tbusy0++;

    lmc_trace(dev, "lmc_ifdown out");

    return 0;
}