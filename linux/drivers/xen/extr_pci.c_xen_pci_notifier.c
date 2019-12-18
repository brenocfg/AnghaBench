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
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 129 
#define  BUS_NOTIFY_DEL_DEVICE 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int xen_add_device (struct device*) ; 
 int xen_remove_device (struct device*) ; 

__attribute__((used)) static int xen_pci_notifier(struct notifier_block *nb,
			    unsigned long action, void *data)
{
	struct device *dev = data;
	int r = 0;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		r = xen_add_device(dev);
		break;
	case BUS_NOTIFY_DEL_DEVICE:
		r = xen_remove_device(dev);
		break;
	default:
		return NOTIFY_DONE;
	}
	if (r)
		dev_err(dev, "Failed to %s - passthrough or MSI/MSI-X might fail!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "add" :
			(action == BUS_NOTIFY_DEL_DEVICE ? "delete" : "?"));
	return NOTIFY_OK;
}