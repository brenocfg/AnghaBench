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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fifo; scalar_t__ dev; int /*<<< orphan*/  region_size; int /*<<< orphan*/  ioport1; int /*<<< orphan*/  irq; int /*<<< orphan*/  input_fifo; int /*<<< orphan*/  input_jog_dev; int /*<<< orphan*/  input_key_dev; int /*<<< orphan*/  input_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (scalar_t__) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  sonypi_disable () ; 
 int /*<<< orphan*/  sonypi_irq ; 
 int /*<<< orphan*/  sonypi_misc_device ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ useinput ; 

__attribute__((used)) static int sonypi_remove(struct platform_device *dev)
{
	sonypi_disable();

	synchronize_irq(sonypi_device.irq);
	flush_work(&sonypi_device.input_work);

	if (useinput) {
		input_unregister_device(sonypi_device.input_key_dev);
		input_unregister_device(sonypi_device.input_jog_dev);
		kfifo_free(&sonypi_device.input_fifo);
	}

	misc_deregister(&sonypi_misc_device);

	free_irq(sonypi_device.irq, sonypi_irq);
	release_region(sonypi_device.ioport1, sonypi_device.region_size);

	if (sonypi_device.dev) {
		pci_disable_device(sonypi_device.dev);
		pci_dev_put(sonypi_device.dev);
	}

	kfifo_free(&sonypi_device.fifo);

	return 0;
}