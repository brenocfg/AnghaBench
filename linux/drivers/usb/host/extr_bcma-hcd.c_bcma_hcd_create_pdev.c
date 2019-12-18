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
typedef  scalar_t__ u32 ;
struct resource {int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_2__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/ * parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct bcma_device {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
typedef  int /*<<< orphan*/  hci_res ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource*) ; 
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,void const*,size_t) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_alloc (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static struct platform_device *bcma_hcd_create_pdev(struct bcma_device *dev,
						    const char *name, u32 addr,
						    const void *data,
						    size_t size)
{
	struct platform_device *hci_dev;
	struct resource hci_res[2];
	int ret;

	memset(hci_res, 0, sizeof(hci_res));

	hci_res[0].start = addr;
	hci_res[0].end = hci_res[0].start + 0x1000 - 1;
	hci_res[0].flags = IORESOURCE_MEM;

	hci_res[1].start = dev->irq;
	hci_res[1].flags = IORESOURCE_IRQ;

	hci_dev = platform_device_alloc(name, 0);
	if (!hci_dev)
		return ERR_PTR(-ENOMEM);

	hci_dev->dev.parent = &dev->dev;
	hci_dev->dev.dma_mask = &hci_dev->dev.coherent_dma_mask;

	ret = platform_device_add_resources(hci_dev, hci_res,
					    ARRAY_SIZE(hci_res));
	if (ret)
		goto err_alloc;
	if (data)
		ret = platform_device_add_data(hci_dev, data, size);
	if (ret)
		goto err_alloc;
	ret = platform_device_add(hci_dev);
	if (ret)
		goto err_alloc;

	return hci_dev;

err_alloc:
	platform_device_put(hci_dev);
	return ERR_PTR(ret);
}