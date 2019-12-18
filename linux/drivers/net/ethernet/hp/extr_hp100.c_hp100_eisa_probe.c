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
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {int dummy; } ;
struct eisa_device {scalar_t__ base_addr; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HP100_BUS_EISA ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int hp100_probe1 (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eisa_device* to_eisa_device (struct device*) ; 

__attribute__((used)) static int hp100_eisa_probe(struct device *gendev)
{
	struct net_device *dev = alloc_etherdev(sizeof(struct hp100_private));
	struct eisa_device *edev = to_eisa_device(gendev);
	int err;

	if (!dev)
		return -ENOMEM;

	SET_NETDEV_DEV(dev, &edev->dev);

	err = hp100_probe1(dev, edev->base_addr + 0xC38, HP100_BUS_EISA, NULL);
	if (err)
		goto out1;

#ifdef HP100_DEBUG
	printk("hp100: %s: EISA adapter found at 0x%x\n", dev->name,
	       dev->base_addr);
#endif
	dev_set_drvdata(gendev, dev);
	return 0;
 out1:
	free_netdev(dev);
	return err;
}