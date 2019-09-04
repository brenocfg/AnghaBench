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
 int SMB_INDEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 TYPE_2__ sis5595_adapter ; 
 int sis5595_base ; 
 int /*<<< orphan*/  sis5595_pdev ; 
 scalar_t__ sis5595_setup (struct pci_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int sis5595_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	int err;

	if (sis5595_setup(dev)) {
		dev_err(&dev->dev, "SIS5595 not detected, module not inserted.\n");
		return -ENODEV;
	}

	/* set up the sysfs linkage to our parent device */
	sis5595_adapter.dev.parent = &dev->dev;

	snprintf(sis5595_adapter.name, sizeof(sis5595_adapter.name),
		 "SMBus SIS5595 adapter at %04x", sis5595_base + SMB_INDEX);
	err = i2c_add_adapter(&sis5595_adapter);
	if (err) {
		release_region(sis5595_base + SMB_INDEX, 2);
		return err;
	}

	/* Always return failure here.  This is to allow other drivers to bind
	 * to this pci device.  We don't really want to have control over the
	 * pci device, we only wanted to read as few register values from it.
	 */
	sis5595_pdev =  pci_dev_get(dev);
	return -ENODEV;
}