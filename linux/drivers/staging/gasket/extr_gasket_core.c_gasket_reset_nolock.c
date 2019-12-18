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
struct gasket_driver_desc {int (* device_reset_cb ) (struct gasket_dev*) ;int num_page_tables; } ;
struct gasket_dev {scalar_t__ status; int /*<<< orphan*/  dev; int /*<<< orphan*/ * page_table; TYPE_1__* internal_desc; } ;
struct TYPE_2__ {struct gasket_driver_desc* driver_desc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GASKET_STATUS_DEAD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gasket_get_hw_status (struct gasket_dev*) ; 
 int gasket_interrupt_reinit (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_page_table_reset (int /*<<< orphan*/ ) ; 
 int stub1 (struct gasket_dev*) ; 

int gasket_reset_nolock(struct gasket_dev *gasket_dev)
{
	int ret;
	int i;
	const struct gasket_driver_desc *driver_desc;

	driver_desc = gasket_dev->internal_desc->driver_desc;
	if (!driver_desc->device_reset_cb)
		return 0;

	ret = driver_desc->device_reset_cb(gasket_dev);
	if (ret) {
		dev_dbg(gasket_dev->dev, "Device reset cb returned %d.\n",
			ret);
		return ret;
	}

	/* Reinitialize the page tables and interrupt framework. */
	for (i = 0; i < driver_desc->num_page_tables; ++i)
		gasket_page_table_reset(gasket_dev->page_table[i]);

	ret = gasket_interrupt_reinit(gasket_dev);
	if (ret) {
		dev_dbg(gasket_dev->dev, "Unable to reinit interrupts: %d.\n",
			ret);
		return ret;
	}

	/* Get current device health. */
	gasket_dev->status = gasket_get_hw_status(gasket_dev);
	if (gasket_dev->status == GASKET_STATUS_DEAD) {
		dev_dbg(gasket_dev->dev, "Device reported as dead.\n");
		return -EINVAL;
	}

	return 0;
}