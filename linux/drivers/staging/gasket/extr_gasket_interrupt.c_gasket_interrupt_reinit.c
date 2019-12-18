#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gasket_dev {int /*<<< orphan*/  dev; TYPE_1__* interrupt_data; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PCI_MSIX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  force_msix_interrupt_unmasking (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_interrupt_msix_cleanup (TYPE_1__*) ; 
 int gasket_interrupt_msix_init (TYPE_1__*) ; 
 int /*<<< orphan*/  gasket_interrupt_setup (struct gasket_dev*) ; 

int gasket_interrupt_reinit(struct gasket_dev *gasket_dev)
{
	int ret;

	if (!gasket_dev->interrupt_data) {
		dev_dbg(gasket_dev->dev,
			"Attempted to reinit uninitialized interrupt data\n");
		return -EINVAL;
	}

	switch (gasket_dev->interrupt_data->type) {
	case PCI_MSIX:
		gasket_interrupt_msix_cleanup(gasket_dev->interrupt_data);
		ret = gasket_interrupt_msix_init(gasket_dev->interrupt_data);
		if (ret)
			break;
		force_msix_interrupt_unmasking(gasket_dev);
		break;

	default:
		ret = -EINVAL;
	}

	if (ret) {
		/* Failing to setup interrupts will cause the device
		 * to report GASKET_STATUS_LAMED, but is not fatal.
		 */
		dev_warn(gasket_dev->dev, "Couldn't reinit interrupts: %d\n",
			 ret);
		return 0;
	}

	gasket_interrupt_setup(gasket_dev);

	return 0;
}