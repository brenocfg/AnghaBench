#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int tx_ProcTimeout; int /*<<< orphan*/  tx_tbusy_calls; } ;
struct TYPE_12__ {int /*<<< orphan*/  lmc_lock; TYPE_3__ extra_stats; TYPE_2__* lmc_device; } ;
typedef  TYPE_4__ lmc_softc_t ;
struct TYPE_9__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int LMC_CSR_READ (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LMC_EVENT_LOG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LMC_EVENT_RESET1 ; 
 int /*<<< orphan*/  LMC_EVENT_RESET2 ; 
 int /*<<< orphan*/  LMC_EVENT_XMTPRCTMO ; 
 scalar_t__ TX_TIMEOUT ; 
 int /*<<< orphan*/  csr_command ; 
 int /*<<< orphan*/  csr_status ; 
 int /*<<< orphan*/  csr_txpoll ; 
 TYPE_4__* dev_to_sc (struct net_device*) ; 
 scalar_t__ dev_trans_start (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int lmc_mii_readreg (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lmc_running_reset (struct net_device*) ; 
 int /*<<< orphan*/  lmc_trace (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lmc_driver_timeout(struct net_device *dev)
{
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 csr6;
    unsigned long flags;

    lmc_trace(dev, "lmc_driver_timeout in");

    spin_lock_irqsave(&sc->lmc_lock, flags);

    printk("%s: Xmitter busy|\n", dev->name);

    sc->extra_stats.tx_tbusy_calls++;
    if (jiffies - dev_trans_start(dev) < TX_TIMEOUT)
	    goto bug_out;

    /*
     * Chip seems to have locked up
     * Reset it
     * This whips out all our decriptor
     * table and starts from scartch
     */

    LMC_EVENT_LOG(LMC_EVENT_XMTPRCTMO,
                  LMC_CSR_READ (sc, csr_status),
		  sc->extra_stats.tx_ProcTimeout);

    lmc_running_reset (dev);

    LMC_EVENT_LOG(LMC_EVENT_RESET1, LMC_CSR_READ (sc, csr_status), 0);
    LMC_EVENT_LOG(LMC_EVENT_RESET2,
                  lmc_mii_readreg (sc, 0, 16),
                  lmc_mii_readreg (sc, 0, 17));

    /* restart the tx processes */
    csr6 = LMC_CSR_READ (sc, csr_command);
    LMC_CSR_WRITE (sc, csr_command, csr6 | 0x0002);
    LMC_CSR_WRITE (sc, csr_command, csr6 | 0x2002);

    /* immediate transmit */
    LMC_CSR_WRITE (sc, csr_txpoll, 0);

    sc->lmc_device->stats.tx_errors++;
    sc->extra_stats.tx_ProcTimeout++; /* -baz */

    netif_trans_update(dev); /* prevent tx timeout */

bug_out:

    spin_unlock_irqrestore(&sc->lmc_lock, flags);

    lmc_trace(dev, "lmc_driver_timeout out");


}