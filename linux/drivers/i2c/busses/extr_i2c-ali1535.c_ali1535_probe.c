#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ ali1535_adapter ; 
 int ali1535_offset ; 
 scalar_t__ ali1535_setup (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int ali1535_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	if (ali1535_setup(dev)) {
		dev_warn(&dev->dev,
			"ALI1535 not detected, module not inserted.\n");
		return -ENODEV;
	}

	/* set up the sysfs linkage to our parent device */
	ali1535_adapter.dev.parent = &dev->dev;

	snprintf(ali1535_adapter.name, sizeof(ali1535_adapter.name),
		"SMBus ALI1535 adapter at %04x", ali1535_offset);
	return i2c_add_adapter(&ali1535_adapter);
}