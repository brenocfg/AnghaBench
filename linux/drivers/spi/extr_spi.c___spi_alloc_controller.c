#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* parent; int /*<<< orphan*/ * class; } ;
struct spi_controller {int bus_num; int num_chipselect; int slave; TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_SPI_SLAVE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_get_cache_alignment () ; 
 struct spi_controller* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spi_controller_set_devdata (struct spi_controller*,void*) ; 
 int /*<<< orphan*/  spi_master_class ; 
 int /*<<< orphan*/  spi_slave_class ; 

struct spi_controller *__spi_alloc_controller(struct device *dev,
					      unsigned int size, bool slave)
{
	struct spi_controller	*ctlr;
	size_t ctlr_size = ALIGN(sizeof(*ctlr), dma_get_cache_alignment());

	if (!dev)
		return NULL;

	ctlr = kzalloc(size + ctlr_size, GFP_KERNEL);
	if (!ctlr)
		return NULL;

	device_initialize(&ctlr->dev);
	ctlr->bus_num = -1;
	ctlr->num_chipselect = 1;
	ctlr->slave = slave;
	if (IS_ENABLED(CONFIG_SPI_SLAVE) && slave)
		ctlr->dev.class = &spi_slave_class;
	else
		ctlr->dev.class = &spi_master_class;
	ctlr->dev.parent = dev;
	pm_suspend_ignore_children(&ctlr->dev, true);
	spi_controller_set_devdata(ctlr, (void *)ctlr + ctlr_size);

	return ctlr;
}