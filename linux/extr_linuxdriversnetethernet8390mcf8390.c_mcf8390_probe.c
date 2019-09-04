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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* ____alloc_ei_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int mcf8390_init (struct net_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mcf8390_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct resource *mem, *irq;
	resource_size_t msize;
	int ret;

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (irq == NULL) {
		dev_err(&pdev->dev, "no IRQ specified?\n");
		return -ENXIO;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (mem == NULL) {
		dev_err(&pdev->dev, "no memory address specified?\n");
		return -ENXIO;
	}
	msize = resource_size(mem);
	if (!request_mem_region(mem->start, msize, pdev->name))
		return -EBUSY;

	dev = ____alloc_ei_netdev(0);
	if (dev == NULL) {
		release_mem_region(mem->start, msize);
		return -ENOMEM;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	platform_set_drvdata(pdev, dev);

	dev->irq = irq->start;
	dev->base_addr = mem->start;

	ret = mcf8390_init(dev);
	if (ret) {
		release_mem_region(mem->start, msize);
		free_netdev(dev);
		return ret;
	}
	return 0;
}