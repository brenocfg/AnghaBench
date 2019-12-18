#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct net_device {unsigned long base_addr; int /*<<< orphan*/  irq; } ;
struct ei_device {unsigned long* reg_offset; int /*<<< orphan*/ * mem; int /*<<< orphan*/  rxcr_base; } ;
struct ax_device {int irqflags; unsigned long* reg_offsets; int /*<<< orphan*/ * map2; TYPE_1__* plat; } ;
struct TYPE_2__ {unsigned long* reg_offsets; int /*<<< orphan*/  rcr_val; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int IORESOURCE_IRQ_SHAREABLE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_MASK ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* ax__alloc_ei_netdev (int) ; 
 int ax_init_dev (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 void* ioremap (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long resource_size (struct resource*) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static int ax_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct ei_device *ei_local;
	struct ax_device *ax;
	struct resource *irq, *mem, *mem2;
	unsigned long mem_size, mem2_size = 0;
	int ret = 0;

	dev = ax__alloc_ei_netdev(sizeof(struct ax_device));
	if (dev == NULL)
		return -ENOMEM;

	/* ok, let's setup our device */
	SET_NETDEV_DEV(dev, &pdev->dev);
	ei_local = netdev_priv(dev);
	ax = to_ax_dev(dev);

	ax->plat = dev_get_platdata(&pdev->dev);
	platform_set_drvdata(pdev, dev);

	ei_local->rxcr_base = ax->plat->rcr_val;

	/* find the platform resources */
	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq) {
		dev_err(&pdev->dev, "no IRQ specified\n");
		ret = -ENXIO;
		goto exit_mem;
	}

	dev->irq = irq->start;
	ax->irqflags = irq->flags & IRQF_TRIGGER_MASK;

	if (irq->flags &  IORESOURCE_IRQ_SHAREABLE)
		ax->irqflags |= IRQF_SHARED;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem) {
		dev_err(&pdev->dev, "no MEM specified\n");
		ret = -ENXIO;
		goto exit_mem;
	}

	mem_size = resource_size(mem);

	/*
	 * setup the register offsets from either the platform data or
	 * by using the size of the resource provided
	 */
	if (ax->plat->reg_offsets)
		ei_local->reg_offset = ax->plat->reg_offsets;
	else {
		ei_local->reg_offset = ax->reg_offsets;
		for (ret = 0; ret < 0x18; ret++)
			ax->reg_offsets[ret] = (mem_size / 0x18) * ret;
	}

	if (!request_mem_region(mem->start, mem_size, pdev->name)) {
		dev_err(&pdev->dev, "cannot reserve registers\n");
		ret = -ENXIO;
		goto exit_mem;
	}

	ei_local->mem = ioremap(mem->start, mem_size);
	dev->base_addr = (unsigned long)ei_local->mem;

	if (ei_local->mem == NULL) {
		dev_err(&pdev->dev, "Cannot ioremap area %pR\n", mem);

		ret = -ENXIO;
		goto exit_req;
	}

	/* look for reset area */
	mem2 = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!mem2) {
		if (!ax->plat->reg_offsets) {
			for (ret = 0; ret < 0x20; ret++)
				ax->reg_offsets[ret] = (mem_size / 0x20) * ret;
		}
	} else {
		mem2_size = resource_size(mem2);

		if (!request_mem_region(mem2->start, mem2_size, pdev->name)) {
			dev_err(&pdev->dev, "cannot reserve registers\n");
			ret = -ENXIO;
			goto exit_mem1;
		}

		ax->map2 = ioremap(mem2->start, mem2_size);
		if (!ax->map2) {
			dev_err(&pdev->dev, "cannot map reset register\n");
			ret = -ENXIO;
			goto exit_mem2;
		}

		ei_local->reg_offset[0x1f] = ax->map2 - ei_local->mem;
	}

	/* got resources, now initialise and register device */
	ret = ax_init_dev(dev);
	if (!ret)
		return 0;

	if (!ax->map2)
		goto exit_mem1;

	iounmap(ax->map2);

 exit_mem2:
	if (mem2)
		release_mem_region(mem2->start, mem2_size);

 exit_mem1:
	iounmap(ei_local->mem);

 exit_req:
	release_mem_region(mem->start, mem_size);

 exit_mem:
	platform_set_drvdata(pdev, NULL);
	free_netdev(dev);

	return ret;
}