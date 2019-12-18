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
struct smc_private {int /*<<< orphan*/  media; scalar_t__ packets_waiting; int /*<<< orphan*/ * saved_skb; struct pcmcia_device* p_dev; } ;
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {scalar_t__ base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 scalar_t__ check_sig (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  media_check ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  smc_dump (struct net_device*) ; 
 int /*<<< orphan*/  smc_reset (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_open(struct net_device *dev)
{
    struct smc_private *smc = netdev_priv(dev);
    struct pcmcia_device *link = smc->p_dev;

    dev_dbg(&link->dev, "%s: smc_open(%p), ID/Window %4.4x.\n",
	  dev->name, dev, inw(dev->base_addr + BANK_SELECT));
#ifdef PCMCIA_DEBUG
    smc_dump(dev);
#endif

    /* Check that the PCMCIA card is still here. */
    if (!pcmcia_dev_present(link))
	return -ENODEV;
    /* Physical device present signature. */
    if (check_sig(link) < 0) {
	netdev_info(dev, "Yikes!  Bad chip signature!\n");
	return -ENODEV;
    }
    link->open++;

    netif_start_queue(dev);
    smc->saved_skb = NULL;
    smc->packets_waiting = 0;

    smc_reset(dev);
    timer_setup(&smc->media, media_check, 0);
    mod_timer(&smc->media, jiffies + HZ);

    return 0;
}