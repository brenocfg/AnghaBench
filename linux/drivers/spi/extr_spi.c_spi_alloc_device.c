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
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct spi_device {TYPE_2__ dev; TYPE_1__ statistics; int /*<<< orphan*/  cs_gpio; struct spi_controller* controller; struct spi_controller* master; } ;
struct spi_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 struct spi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_type ; 
 int /*<<< orphan*/  spi_controller_get (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_controller_put (struct spi_controller*) ; 
 int /*<<< orphan*/  spidev_release ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct spi_device *spi_alloc_device(struct spi_controller *ctlr)
{
	struct spi_device	*spi;

	if (!spi_controller_get(ctlr))
		return NULL;

	spi = kzalloc(sizeof(*spi), GFP_KERNEL);
	if (!spi) {
		spi_controller_put(ctlr);
		return NULL;
	}

	spi->master = spi->controller = ctlr;
	spi->dev.parent = &ctlr->dev;
	spi->dev.bus = &spi_bus_type;
	spi->dev.release = spidev_release;
	spi->cs_gpio = -ENOENT;

	spin_lock_init(&spi->statistics.lock);

	device_initialize(&spi->dev);
	return spi;
}