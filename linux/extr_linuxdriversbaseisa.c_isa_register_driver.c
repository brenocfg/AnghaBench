#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct isa_driver {TYPE_1__* devices; TYPE_2__ driver; } ;
struct TYPE_6__ {struct isa_driver* platform_data; int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct isa_dev {unsigned int id; TYPE_1__ dev; TYPE_1__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int driver_register (TYPE_2__*) ; 
 int /*<<< orphan*/  isa_bus ; 
 int /*<<< orphan*/  isa_bus_type ; 
 int /*<<< orphan*/  isa_dev_release ; 
 int /*<<< orphan*/  isa_unregister_driver (struct isa_driver*) ; 
 struct isa_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

int isa_register_driver(struct isa_driver *isa_driver, unsigned int ndev)
{
	int error;
	unsigned int id;

	isa_driver->driver.bus	= &isa_bus_type;
	isa_driver->devices	= NULL;

	error = driver_register(&isa_driver->driver);
	if (error)
		return error;

	for (id = 0; id < ndev; id++) {
		struct isa_dev *isa_dev;

		isa_dev = kzalloc(sizeof *isa_dev, GFP_KERNEL);
		if (!isa_dev) {
			error = -ENOMEM;
			break;
		}

		isa_dev->dev.parent	= &isa_bus;
		isa_dev->dev.bus	= &isa_bus_type;

		dev_set_name(&isa_dev->dev, "%s.%u",
			     isa_driver->driver.name, id);
		isa_dev->dev.platform_data	= isa_driver;
		isa_dev->dev.release		= isa_dev_release;
		isa_dev->id			= id;

		isa_dev->dev.coherent_dma_mask = DMA_BIT_MASK(24);
		isa_dev->dev.dma_mask = &isa_dev->dev.coherent_dma_mask;

		error = device_register(&isa_dev->dev);
		if (error) {
			put_device(&isa_dev->dev);
			break;
		}

		if (isa_dev->dev.platform_data) {
			isa_dev->next = isa_driver->devices;
			isa_driver->devices = &isa_dev->dev;
		} else
			device_unregister(&isa_dev->dev);
	}

	if (!error && !isa_driver->devices)
		error = -ENODEV;

	if (error)
		isa_unregister_driver(isa_driver);

	return error;
}