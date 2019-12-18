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
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {unsigned int base_addr; } ;
struct TYPE_3__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MACEBANK (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  nmclan_reset (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 

__attribute__((used)) static int mace_open(struct net_device *dev)
{
  unsigned int ioaddr = dev->base_addr;
  mace_private *lp = netdev_priv(dev);
  struct pcmcia_device *link = lp->p_dev;

  if (!pcmcia_dev_present(link))
    return -ENODEV;

  link->open++;

  MACEBANK(0);

  netif_start_queue(dev);
  nmclan_reset(dev);

  return 0; /* Always succeed */
}