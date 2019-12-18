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
struct xen_pcibk_dev_data {int isr_on; int ack_intr; int /*<<< orphan*/  irq_name; } ;
struct pcistub_device {TYPE_1__* dev; } ;
struct device_driver {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 struct xen_pcibk_dev_data* pci_get_drvdata (TYPE_1__*) ; 
 struct pcistub_device* pcistub_device_find (int,int,int,int) ; 
 int /*<<< orphan*/  pcistub_device_put (struct pcistub_device*) ; 
 int str_to_slot (char const*,int*,int*,int*,int*) ; 

__attribute__((used)) static ssize_t irq_handler_state_store(struct device_driver *drv,
				       const char *buf, size_t count)
{
	struct pcistub_device *psdev;
	struct xen_pcibk_dev_data *dev_data;
	int domain, bus, slot, func;
	int err;

	err = str_to_slot(buf, &domain, &bus, &slot, &func);
	if (err)
		return err;

	psdev = pcistub_device_find(domain, bus, slot, func);
	if (!psdev) {
		err = -ENOENT;
		goto out;
	}

	dev_data = pci_get_drvdata(psdev->dev);
	if (!dev_data) {
		err = -ENOENT;
		goto out;
	}

	dev_dbg(&psdev->dev->dev, "%s fake irq handler: %d->%d\n",
		dev_data->irq_name, dev_data->isr_on,
		!dev_data->isr_on);

	dev_data->isr_on = !(dev_data->isr_on);
	if (dev_data->isr_on)
		dev_data->ack_intr = 1;
out:
	if (psdev)
		pcistub_device_put(psdev);
	if (!err)
		err = count;
	return err;
}