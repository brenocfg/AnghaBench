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
struct spi_device {int dummy; } ;
struct pi433_device {struct pi433_device* rx_buffer; int /*<<< orphan*/  cdev; int /*<<< orphan*/  devt; int /*<<< orphan*/  tx_task_struct; int /*<<< orphan*/ * spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_gpio (struct pi433_device*) ; 
 int /*<<< orphan*/  kfree (struct pi433_device*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi433_class ; 
 int /*<<< orphan*/  pi433_free_minor (struct pi433_device*) ; 
 struct pi433_device* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int pi433_remove(struct spi_device *spi)
{
	struct pi433_device	*device = spi_get_drvdata(spi);

	/* free GPIOs */
	free_gpio(device);

	/* make sure ops on existing fds can abort cleanly */
	device->spi = NULL;

	kthread_stop(device->tx_task_struct);

	device_destroy(pi433_class, device->devt);

	cdev_del(device->cdev);

	pi433_free_minor(device);

	kfree(device->rx_buffer);
	kfree(device);

	return 0;
}