#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int /*<<< orphan*/  socket; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_reset_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void mace_tx_timeout(struct net_device *dev)
{
  mace_private *lp = netdev_priv(dev);
  struct pcmcia_device *link = lp->p_dev;

  netdev_notice(dev, "transmit timed out -- ");
#if RESET_ON_TIMEOUT
  pr_cont("resetting card\n");
  pcmcia_reset_card(link->socket);
#else /* #if RESET_ON_TIMEOUT */
  pr_cont("NOT resetting card\n");
#endif /* #if RESET_ON_TIMEOUT */
  netif_trans_update(dev); /* prevent tx timeout */
  netif_wake_queue(dev);
}