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
struct spi_device {int chip_select; int /*<<< orphan*/  dev; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  cs_gpiod; struct spi_controller* controller; } ;
struct TYPE_2__ {struct device* parent; } ;
struct spi_controller {int num_chipselect; int /*<<< orphan*/ * cs_gpios; int /*<<< orphan*/ * cs_gpiods; TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int EINVAL ; 
 int bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int dev_name (int /*<<< orphan*/ *) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_bus_type ; 
 int /*<<< orphan*/  spi_dev_check ; 
 int /*<<< orphan*/  spi_dev_set_name (struct spi_device*) ; 
 int spi_setup (struct spi_device*) ; 

int spi_add_device(struct spi_device *spi)
{
	static DEFINE_MUTEX(spi_add_lock);
	struct spi_controller *ctlr = spi->controller;
	struct device *dev = ctlr->dev.parent;
	int status;

	/* Chipselects are numbered 0..max; validate. */
	if (spi->chip_select >= ctlr->num_chipselect) {
		dev_err(dev, "cs%d >= max %d\n", spi->chip_select,
			ctlr->num_chipselect);
		return -EINVAL;
	}

	/* Set the bus ID string */
	spi_dev_set_name(spi);

	/* We need to make sure there's no other device with this
	 * chipselect **BEFORE** we call setup(), else we'll trash
	 * its configuration.  Lock against concurrent add() calls.
	 */
	mutex_lock(&spi_add_lock);

	status = bus_for_each_dev(&spi_bus_type, NULL, spi, spi_dev_check);
	if (status) {
		dev_err(dev, "chipselect %d already in use\n",
				spi->chip_select);
		goto done;
	}

	/* Descriptors take precedence */
	if (ctlr->cs_gpiods)
		spi->cs_gpiod = ctlr->cs_gpiods[spi->chip_select];
	else if (ctlr->cs_gpios)
		spi->cs_gpio = ctlr->cs_gpios[spi->chip_select];

	/* Drivers may modify this initial i/o setup, but will
	 * normally rely on the device being setup.  Devices
	 * using SPI_CS_HIGH can't coexist well otherwise...
	 */
	status = spi_setup(spi);
	if (status < 0) {
		dev_err(dev, "can't setup %s, status %d\n",
				dev_name(&spi->dev), status);
		goto done;
	}

	/* Device may be bound to an active driver when this returns */
	status = device_add(&spi->dev);
	if (status < 0)
		dev_err(dev, "can't add %s, status %d\n",
				dev_name(&spi->dev), status);
	else
		dev_dbg(dev, "registered child %s\n", dev_name(&spi->dev));

done:
	mutex_unlock(&spi_add_lock);
	return status;
}