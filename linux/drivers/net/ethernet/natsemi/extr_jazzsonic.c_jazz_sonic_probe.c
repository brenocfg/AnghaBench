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
struct sonic_local {int /*<<< orphan*/ * device; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SONIC_MEM_SIZE ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_boot_setup_check (struct net_device*) ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sonic_msg_init (struct net_device*) ; 
 int sonic_probe1 (struct net_device*) ; 

__attribute__((used)) static int jazz_sonic_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct sonic_local *lp;
	struct resource *res;
	int err = 0;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	dev = alloc_etherdev(sizeof(struct sonic_local));
	if (!dev)
		return -ENOMEM;

	lp = netdev_priv(dev);
	lp->device = &pdev->dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	platform_set_drvdata(pdev, dev);

	netdev_boot_setup_check(dev);

	dev->base_addr = res->start;
	dev->irq = platform_get_irq(pdev, 0);
	err = sonic_probe1(dev);
	if (err)
		goto out;

	pr_info("SONIC ethernet @%08lx, MAC %pM, IRQ %d\n",
		dev->base_addr, dev->dev_addr, dev->irq);

	sonic_msg_init(dev);

	err = register_netdev(dev);
	if (err)
		goto out1;

	return 0;

out1:
	release_mem_region(dev->base_addr, SONIC_MEM_SIZE);
out:
	free_netdev(dev);

	return err;
}