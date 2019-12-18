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
 int SMB_STS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 TYPE_2__ sis630_adapter ; 
 scalar_t__ sis630_setup (struct pci_dev*) ; 
 int smbus_base ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int sis630_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	if (sis630_setup(dev)) {
		dev_err(&dev->dev,
			"SIS630 compatible bus not detected, "
			"module not inserted.\n");
		return -ENODEV;
	}

	/* set up the sysfs linkage to our parent device */
	sis630_adapter.dev.parent = &dev->dev;

	snprintf(sis630_adapter.name, sizeof(sis630_adapter.name),
		 "SMBus SIS630 adapter at %04x", smbus_base + SMB_STS);

	return i2c_add_adapter(&sis630_adapter);
}