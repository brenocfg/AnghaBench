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
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net2272 {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  base_shift; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int BYTE_SWAP ; 
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_BUS ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int IORESOURCE_IRQ_HIGHEDGE ; 
 int IORESOURCE_IRQ_HIGHLEVEL ; 
 int IORESOURCE_IRQ_LOWEDGE ; 
 int IORESOURCE_IRQ_LOWLEVEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 unsigned int IRQF_TRIGGER_FALLING ; 
 unsigned int IRQF_TRIGGER_HIGH ; 
 unsigned int IRQF_TRIGGER_LOW ; 
 unsigned int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct net2272*) ; 
 int /*<<< orphan*/  LOCCTL ; 
 int PTR_ERR (struct net2272*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int net2272_probe_fin (struct net2272*,unsigned int) ; 
 struct net2272* net2272_probe_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int net2272_read (struct net2272*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net2272*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int
net2272_plat_probe(struct platform_device *pdev)
{
	struct net2272 *dev;
	int ret;
	unsigned int irqflags;
	resource_size_t base, len;
	struct resource *iomem, *iomem_bus, *irq_res;

	irq_res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	iomem_bus = platform_get_resource(pdev, IORESOURCE_BUS, 0);
	if (!irq_res || !iomem) {
		dev_err(&pdev->dev, "must provide irq/base addr");
		return -EINVAL;
	}

	dev = net2272_probe_init(&pdev->dev, irq_res->start);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	irqflags = 0;
	if (irq_res->flags & IORESOURCE_IRQ_HIGHEDGE)
		irqflags |= IRQF_TRIGGER_RISING;
	if (irq_res->flags & IORESOURCE_IRQ_LOWEDGE)
		irqflags |= IRQF_TRIGGER_FALLING;
	if (irq_res->flags & IORESOURCE_IRQ_HIGHLEVEL)
		irqflags |= IRQF_TRIGGER_HIGH;
	if (irq_res->flags & IORESOURCE_IRQ_LOWLEVEL)
		irqflags |= IRQF_TRIGGER_LOW;

	base = iomem->start;
	len = resource_size(iomem);
	if (iomem_bus)
		dev->base_shift = iomem_bus->start;

	if (!request_mem_region(base, len, driver_name)) {
		dev_dbg(dev->dev, "get request memory region!\n");
		ret = -EBUSY;
		goto err;
	}
	dev->base_addr = ioremap_nocache(base, len);
	if (!dev->base_addr) {
		dev_dbg(dev->dev, "can't map memory\n");
		ret = -EFAULT;
		goto err_req;
	}

	ret = net2272_probe_fin(dev, IRQF_TRIGGER_LOW);
	if (ret)
		goto err_io;

	platform_set_drvdata(pdev, dev);
	dev_info(&pdev->dev, "running in 16-bit, %sbyte swap local bus mode\n",
		(net2272_read(dev, LOCCTL) & (1 << BYTE_SWAP)) ? "" : "no ");

	return 0;

 err_io:
	iounmap(dev->base_addr);
 err_req:
	release_mem_region(base, len);
 err:
	return ret;
}