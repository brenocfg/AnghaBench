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
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct axis_fifo {TYPE_1__* mem; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  devt; struct device* device; int /*<<< orphan*/  char_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  axis_fifo_attrs_group ; 
 int /*<<< orphan*/  axis_fifo_driver_class ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 struct axis_fifo* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct axis_fifo*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axis_fifo_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct axis_fifo *fifo = dev_get_drvdata(dev);

	sysfs_remove_group(&fifo->device->kobj, &axis_fifo_attrs_group);
	cdev_del(&fifo->char_device);
	dev_set_drvdata(fifo->device, NULL);
	device_destroy(axis_fifo_driver_class, fifo->devt);
	unregister_chrdev_region(fifo->devt, 1);
	free_irq(fifo->irq, fifo);
	iounmap(fifo->base_addr);
	release_mem_region(fifo->mem->start, resource_size(fifo->mem));
	dev_set_drvdata(dev, NULL);
	return 0;
}