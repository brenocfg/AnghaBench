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
typedef  int /*<<< orphan*/  u64 ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* parent; void* platform_data; int /*<<< orphan*/  coherent_dma_mask; } ;
struct amba_device {int* irq; unsigned int periphid; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct amba_device* ERR_PTR (int) ; 
 int amba_device_add (struct amba_device*,struct resource*) ; 
 struct amba_device* amba_device_alloc (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  amba_device_put (struct amba_device*) ; 

__attribute__((used)) static struct amba_device *
amba_aphb_device_add(struct device *parent, const char *name,
		     resource_size_t base, size_t size, int irq1, int irq2,
		     void *pdata, unsigned int periphid, u64 dma_mask,
		     struct resource *resbase)
{
	struct amba_device *dev;
	int ret;

	dev = amba_device_alloc(name, base, size);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	dev->dev.coherent_dma_mask = dma_mask;
	dev->irq[0] = irq1;
	dev->irq[1] = irq2;
	dev->periphid = periphid;
	dev->dev.platform_data = pdata;
	dev->dev.parent = parent;

	ret = amba_device_add(dev, resbase);
	if (ret) {
		amba_device_put(dev);
		return ERR_PTR(ret);
	}

	return dev;
}