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
struct pcmcia_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  open; } ;
struct net_device {scalar_t__ base_addr; int /*<<< orphan*/  name; } ;
struct el3_private {int /*<<< orphan*/  media; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 scalar_t__ EL3_STATUS ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  media_check ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  tc589_reset (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int el3_open(struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	struct pcmcia_device *link = lp->p_dev;

	if (!pcmcia_dev_present(link))
		return -ENODEV;

	link->open++;
	netif_start_queue(dev);

	tc589_reset(dev);
	timer_setup(&lp->media, media_check, 0);
	mod_timer(&lp->media, jiffies + HZ);

	dev_dbg(&link->dev, "%s: opened, status %4.4x.\n",
	  dev->name, inw(dev->base_addr + EL3_STATUS));

	return 0;
}