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
struct gasket_interrupt_data {int type; struct gasket_interrupt_data* eventfd_ctxs; void* interrupt_counts; scalar_t__ num_configured; int /*<<< orphan*/  pack_width; int /*<<< orphan*/  interrupt_bar_index; int /*<<< orphan*/  interrupts; int /*<<< orphan*/  num_interrupts; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  name; } ;
struct gasket_driver_desc {int interrupt_type; int /*<<< orphan*/  num_interrupts; int /*<<< orphan*/  interrupt_pack_width; int /*<<< orphan*/  interrupt_bar_index; int /*<<< orphan*/  interrupts; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct gasket_dev {TYPE_1__ dev_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  pci_dev; struct gasket_interrupt_data* interrupt_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PCI_MSIX 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  force_msix_interrupt_unmasking (struct gasket_dev*) ; 
 struct gasket_driver_desc* gasket_get_driver_desc (struct gasket_dev*) ; 
 int gasket_interrupt_msix_init (struct gasket_interrupt_data*) ; 
 int /*<<< orphan*/  gasket_interrupt_setup (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_sysfs_create_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_sysfs_attrs ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gasket_interrupt_data*) ; 
 struct gasket_interrupt_data* kzalloc (int,int /*<<< orphan*/ ) ; 

int gasket_interrupt_init(struct gasket_dev *gasket_dev)
{
	int ret;
	struct gasket_interrupt_data *interrupt_data;
	const struct gasket_driver_desc *driver_desc =
		gasket_get_driver_desc(gasket_dev);

	interrupt_data = kzalloc(sizeof(*interrupt_data), GFP_KERNEL);
	if (!interrupt_data)
		return -ENOMEM;
	gasket_dev->interrupt_data = interrupt_data;
	interrupt_data->name = driver_desc->name;
	interrupt_data->type = driver_desc->interrupt_type;
	interrupt_data->pci_dev = gasket_dev->pci_dev;
	interrupt_data->num_interrupts = driver_desc->num_interrupts;
	interrupt_data->interrupts = driver_desc->interrupts;
	interrupt_data->interrupt_bar_index = driver_desc->interrupt_bar_index;
	interrupt_data->pack_width = driver_desc->interrupt_pack_width;
	interrupt_data->num_configured = 0;

	interrupt_data->eventfd_ctxs =
		kcalloc(driver_desc->num_interrupts,
			sizeof(*interrupt_data->eventfd_ctxs), GFP_KERNEL);
	if (!interrupt_data->eventfd_ctxs) {
		kfree(interrupt_data);
		return -ENOMEM;
	}

	interrupt_data->interrupt_counts =
		kcalloc(driver_desc->num_interrupts,
			sizeof(*interrupt_data->interrupt_counts), GFP_KERNEL);
	if (!interrupt_data->interrupt_counts) {
		kfree(interrupt_data->eventfd_ctxs);
		kfree(interrupt_data);
		return -ENOMEM;
	}

	switch (interrupt_data->type) {
	case PCI_MSIX:
		ret = gasket_interrupt_msix_init(interrupt_data);
		if (ret)
			break;
		force_msix_interrupt_unmasking(gasket_dev);
		break;

	default:
		ret = -EINVAL;
	}

	if (ret) {
		/* Failing to setup interrupts will cause the device to report
		 * GASKET_STATUS_LAMED. But it is not fatal.
		 */
		dev_warn(gasket_dev->dev,
			 "Couldn't initialize interrupts: %d\n", ret);
		return 0;
	}

	gasket_interrupt_setup(gasket_dev);
	gasket_sysfs_create_entries(gasket_dev->dev_info.device,
				    interrupt_sysfs_attrs);

	return 0;
}