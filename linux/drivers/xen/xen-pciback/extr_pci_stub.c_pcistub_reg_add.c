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
struct pcistub_device {struct pci_dev* dev; } ;
struct pci_dev {int dummy; } ;
struct config_field {unsigned int offset; unsigned int size; unsigned int mask; int /*<<< orphan*/  clean; int /*<<< orphan*/ * release; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * init; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct config_field*) ; 
 struct config_field* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pcistub_device* pcistub_device_find (int,int,int,int) ; 
 int /*<<< orphan*/  pcistub_device_put (struct pcistub_device*) ; 
 int /*<<< orphan*/  xen_pcibk_config_field_free ; 
 int xen_pcibk_config_quirks_add_field (struct pci_dev*,struct config_field*) ; 

__attribute__((used)) static int pcistub_reg_add(int domain, int bus, int slot, int func,
			   unsigned int reg, unsigned int size,
			   unsigned int mask)
{
	int err = 0;
	struct pcistub_device *psdev;
	struct pci_dev *dev;
	struct config_field *field;

	if (reg > 0xfff || (size < 4 && (mask >> (size * 8))))
		return -EINVAL;

	psdev = pcistub_device_find(domain, bus, slot, func);
	if (!psdev) {
		err = -ENODEV;
		goto out;
	}
	dev = psdev->dev;

	field = kzalloc(sizeof(*field), GFP_KERNEL);
	if (!field) {
		err = -ENOMEM;
		goto out;
	}

	field->offset = reg;
	field->size = size;
	field->mask = mask;
	field->init = NULL;
	field->reset = NULL;
	field->release = NULL;
	field->clean = xen_pcibk_config_field_free;

	err = xen_pcibk_config_quirks_add_field(dev, field);
	if (err)
		kfree(field);
out:
	if (psdev)
		pcistub_device_put(psdev);
	return err;
}