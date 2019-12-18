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
struct smc_private {int /*<<< orphan*/  media; struct pcmcia_device* p_dev; } ;
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 scalar_t__ CONTROL ; 
 int /*<<< orphan*/  CTL_POWERDOWN ; 
 scalar_t__ INTERRUPT ; 
 scalar_t__ RCR ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 scalar_t__ TCR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  mask_bits (int,scalar_t__) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smc_close(struct net_device *dev)
{
    struct smc_private *smc = netdev_priv(dev);
    struct pcmcia_device *link = smc->p_dev;
    unsigned int ioaddr = dev->base_addr;

    dev_dbg(&link->dev, "%s: smc_close(), status %4.4x.\n",
	  dev->name, inw(ioaddr + BANK_SELECT));

    netif_stop_queue(dev);

    /* Shut off all interrupts, and turn off the Tx and Rx sections.
       Don't bother to check for chip present. */
    SMC_SELECT_BANK(2);	/* Nominally paranoia, but do no assume... */
    outw(0, ioaddr + INTERRUPT);
    SMC_SELECT_BANK(0);
    mask_bits(0xff00, ioaddr + RCR);
    mask_bits(0xff00, ioaddr + TCR);

    /* Put the chip into power-down mode. */
    SMC_SELECT_BANK(1);
    outw(CTL_POWERDOWN, ioaddr + CONTROL );

    link->open--;
    del_timer_sync(&smc->media);

    return 0;
}