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
struct pcmcia_device {scalar_t__ open; struct com20020_dev* priv; } ;
struct net_device {int base_addr; } ;
struct com20020_dev {struct net_device* dev; } ;
struct arcnet_local {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM20020_REG_W_CONFIG ; 
 int /*<<< orphan*/  arcnet_outb (int,int,int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int com20020_resume(struct pcmcia_device *link)
{
	struct com20020_dev *info = link->priv;
	struct net_device *dev = info->dev;

	if (link->open) {
		int ioaddr = dev->base_addr;
		struct arcnet_local *lp = netdev_priv(dev);

		arcnet_outb(lp->config | 0x80, ioaddr, COM20020_REG_W_CONFIG);
		udelay(5);
		arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	}

	return 0;
}