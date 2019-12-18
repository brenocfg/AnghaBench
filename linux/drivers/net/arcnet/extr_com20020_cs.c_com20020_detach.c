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
struct pcmcia_device {int /*<<< orphan*/  dev; struct com20020_dev* priv; } ;
struct net_device {scalar_t__ irq; } ;
struct com20020_dev {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  com20020_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct com20020_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void com20020_detach(struct pcmcia_device *link)
{
	struct com20020_dev *info = link->priv;
	struct net_device *dev = info->dev;

	dev_dbg(&link->dev, "detach...\n");

	dev_dbg(&link->dev, "com20020_detach\n");

	dev_dbg(&link->dev, "unregister...\n");

	unregister_netdev(dev);

	/* this is necessary because we register our IRQ separately
	 * from card services.
	 */
	if (dev->irq)
		free_irq(dev->irq, dev);

	com20020_release(link);

	/* Unlink device structure, free bits */
	dev_dbg(&link->dev, "unlinking...\n");
	if (link->priv) {
		dev = info->dev;
		if (dev) {
			dev_dbg(&link->dev, "kfree...\n");
			free_netdev(dev);
		}
		dev_dbg(&link->dev, "kfree2...\n");
		kfree(info);
	}

}