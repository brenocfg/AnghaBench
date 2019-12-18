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
struct spi_device {struct spi_device* driver_override; TYPE_1__* controller; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct spi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct spi_device*) ; 
 int /*<<< orphan*/  spi_controller_put (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static void spidev_release(struct device *dev)
{
	struct spi_device	*spi = to_spi_device(dev);

	/* spi controllers may cleanup for released devices */
	if (spi->controller->cleanup)
		spi->controller->cleanup(spi);

	spi_controller_put(spi->controller);
	kfree(spi->driver_override);
	kfree(spi);
}