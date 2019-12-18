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
typedef  void* u32 ;
struct pci_driver {struct pci_device_id* id_table; } ;
struct pci_device_id {unsigned long driver_data; scalar_t__ class_mask; scalar_t__ subvendor; scalar_t__ vendor; } ;
struct pci_dev {void* class; void* subsystem_device; void* subsystem_vendor; void* device; void* vendor; } ;
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PCI_ANY_ID ; 
 int /*<<< orphan*/  kfree (struct pci_dev*) ; 
 struct pci_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pci_add_dynid (struct pci_driver*,void*,void*,void*,void*,void*,void*,unsigned long) ; 
 scalar_t__ pci_match_id (struct pci_device_id*,struct pci_dev*) ; 
 int sscanf (char const*,char*,void**,void**,void**,void**,void**,void**,unsigned long*) ; 
 struct pci_driver* to_pci_driver (struct device_driver*) ; 

__attribute__((used)) static ssize_t new_id_store(struct device_driver *driver, const char *buf,
			    size_t count)
{
	struct pci_driver *pdrv = to_pci_driver(driver);
	const struct pci_device_id *ids = pdrv->id_table;
	u32 vendor, device, subvendor = PCI_ANY_ID,
		subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
	unsigned long driver_data = 0;
	int fields = 0;
	int retval = 0;

	fields = sscanf(buf, "%x %x %x %x %x %x %lx",
			&vendor, &device, &subvendor, &subdevice,
			&class, &class_mask, &driver_data);
	if (fields < 2)
		return -EINVAL;

	if (fields != 7) {
		struct pci_dev *pdev = kzalloc(sizeof(*pdev), GFP_KERNEL);
		if (!pdev)
			return -ENOMEM;

		pdev->vendor = vendor;
		pdev->device = device;
		pdev->subsystem_vendor = subvendor;
		pdev->subsystem_device = subdevice;
		pdev->class = class;

		if (pci_match_id(pdrv->id_table, pdev))
			retval = -EEXIST;

		kfree(pdev);

		if (retval)
			return retval;
	}

	/* Only accept driver_data values that match an existing id_table
	   entry */
	if (ids) {
		retval = -EINVAL;
		while (ids->vendor || ids->subvendor || ids->class_mask) {
			if (driver_data == ids->driver_data) {
				retval = 0;
				break;
			}
			ids++;
		}
		if (retval)	/* No match */
			return retval;
	}

	retval = pci_add_dynid(pdrv, vendor, device, subvendor, subdevice,
			       class, class_mask, driver_data);
	if (retval)
		return retval;
	return count;
}