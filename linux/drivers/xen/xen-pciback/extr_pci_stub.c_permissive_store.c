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
struct xen_pcibk_dev_data {int permissive; } ;
struct pcistub_device {TYPE_1__* dev; } ;
struct device_driver {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct xen_pcibk_dev_data* pci_get_drvdata (TYPE_1__*) ; 
 struct pcistub_device* pcistub_device_find (int,int,int,int) ; 
 int /*<<< orphan*/  pcistub_device_put (struct pcistub_device*) ; 
 int str_to_slot (char const*,int*,int*,int*,int*) ; 

__attribute__((used)) static ssize_t permissive_store(struct device_driver *drv, const char *buf,
				size_t count)
{
	int domain, bus, slot, func;
	int err;
	struct pcistub_device *psdev;
	struct xen_pcibk_dev_data *dev_data;

	err = str_to_slot(buf, &domain, &bus, &slot, &func);
	if (err)
		goto out;

	psdev = pcistub_device_find(domain, bus, slot, func);
	if (!psdev) {
		err = -ENODEV;
		goto out;
	}

	dev_data = pci_get_drvdata(psdev->dev);
	/* the driver data for a device should never be null at this point */
	if (!dev_data) {
		err = -ENXIO;
		goto release;
	}
	if (!dev_data->permissive) {
		dev_data->permissive = 1;
		/* Let user know that what they're doing could be unsafe */
		dev_warn(&psdev->dev->dev, "enabling permissive mode "
			 "configuration space accesses!\n");
		dev_warn(&psdev->dev->dev,
			 "permissive mode is potentially unsafe!\n");
	}
release:
	pcistub_device_put(psdev);
out:
	if (!err)
		err = count;
	return err;
}