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
struct sym_device {int /*<<< orphan*/  chip; struct pci_dev* pdev; } ;
struct sym_chip {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  revision; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {unsigned long* excludes; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sym_chip*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__ sym_driver_setup ; 
 struct sym_chip* sym_lookup_chip_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sym_check_supported(struct sym_device *device)
{
	struct sym_chip *chip;
	struct pci_dev *pdev = device->pdev;
	unsigned long io_port = pci_resource_start(pdev, 0);
	int i;

	/*
	 *  If user excluded this chip, do not initialize it.
	 *  I hate this code so much.  Must kill it.
	 */
	if (io_port) {
		for (i = 0 ; i < 8 ; i++) {
			if (sym_driver_setup.excludes[i] == io_port)
				return -ENODEV;
		}
	}

	/*
	 * Check if the chip is supported.  Then copy the chip description
	 * to our device structure so we can make it match the actual device
	 * and options.
	 */
	chip = sym_lookup_chip_table(pdev->device, pdev->revision);
	if (!chip) {
		dev_info(&pdev->dev, "device not supported\n");
		return -ENODEV;
	}
	memcpy(&device->chip, chip, sizeof(device->chip));

	return 0;
}