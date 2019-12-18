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
struct smc_private {int /*<<< orphan*/ * saved_skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 int inw (unsigned int) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*,int,int) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  smc_reset (struct net_device*) ; 

__attribute__((used)) static void smc_tx_timeout(struct net_device *dev)
{
    struct smc_private *smc = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;

    netdev_notice(dev, "transmit timed out, Tx_status %2.2x status %4.4x.\n",
		  inw(ioaddr)&0xff, inw(ioaddr + 2));
    dev->stats.tx_errors++;
    smc_reset(dev);
    netif_trans_update(dev); /* prevent tx timeout */
    smc->saved_skb = NULL;
    netif_wake_queue(dev);
}