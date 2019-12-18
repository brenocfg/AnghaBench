#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  flags; scalar_t__ end; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pismo_mem {scalar_t__ size; int /*<<< orphan*/  base; } ;
struct pismo_data {struct platform_device** dev; TYPE_2__* client; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,void*,size_t) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int pismo_add_device(struct pismo_data *pismo, int i,
			    struct pismo_mem *region, const char *name,
			    void *pdata, size_t psize)
{
	struct platform_device *dev;
	struct resource res = { };
	phys_addr_t base = region->base;
	int ret;

	if (base == ~0)
		return -ENXIO;

	res.start = base;
	res.end = base + region->size - 1;
	res.flags = IORESOURCE_MEM;

	dev = platform_device_alloc(name, i);
	if (!dev)
		return -ENOMEM;
	dev->dev.parent = &pismo->client->dev;

	do {
		ret = platform_device_add_resources(dev, &res, 1);
		if (ret)
			break;

		ret = platform_device_add_data(dev, pdata, psize);
		if (ret)
			break;

		ret = platform_device_add(dev);
		if (ret)
			break;

		pismo->dev[i] = dev;
		return 0;
	} while (0);

	platform_device_put(dev);
	return ret;
}