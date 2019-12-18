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
struct spi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reset_out; int /*<<< orphan*/  po; int /*<<< orphan*/  reset; int /*<<< orphan*/  mrdy; int /*<<< orphan*/  srdy; } ;
struct ifx_spi_device {TYPE_1__ gpio; int /*<<< orphan*/  io_work_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ifx_spi_device*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifx_spi_free_device (struct ifx_spi_device*) ; 
 int /*<<< orphan*/ * saved_ifx_dev ; 
 struct ifx_spi_device* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ifx_spi_spi_remove(struct spi_device *spi)
{
	struct ifx_spi_device *ifx_dev = spi_get_drvdata(spi);
	/* stop activity */
	tasklet_kill(&ifx_dev->io_work_tasklet);
	/* free irq */
	free_irq(gpio_to_irq(ifx_dev->gpio.reset_out), ifx_dev);
	free_irq(gpio_to_irq(ifx_dev->gpio.srdy), ifx_dev);

	gpio_free(ifx_dev->gpio.srdy);
	gpio_free(ifx_dev->gpio.mrdy);
	gpio_free(ifx_dev->gpio.reset);
	gpio_free(ifx_dev->gpio.po);
	gpio_free(ifx_dev->gpio.reset_out);

	/* free allocations */
	ifx_spi_free_device(ifx_dev);

	saved_ifx_dev = NULL;
	return 0;
}