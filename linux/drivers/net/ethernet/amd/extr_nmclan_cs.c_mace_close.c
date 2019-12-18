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
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct pcmcia_device* p_dev; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 scalar_t__ AM2150_MACE_BASE ; 
 scalar_t__ MACE_IMR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int mace_close(struct net_device *dev)
{
  unsigned int ioaddr = dev->base_addr;
  mace_private *lp = netdev_priv(dev);
  struct pcmcia_device *link = lp->p_dev;

  dev_dbg(&link->dev, "%s: shutting down ethercard.\n", dev->name);

  /* Mask off all interrupts from the MACE chip. */
  outb(0xFF, ioaddr + AM2150_MACE_BASE + MACE_IMR);

  link->open--;
  netif_stop_queue(dev);

  return 0;
}