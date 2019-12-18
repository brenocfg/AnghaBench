#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gasket_driver_desc {int num_page_tables; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdev; scalar_t__ cdev_added; } ;
struct gasket_dev {scalar_t__* page_table; int /*<<< orphan*/  status; TYPE_2__ dev_info; TYPE_1__* internal_desc; } ;
struct TYPE_3__ {struct gasket_driver_desc* driver_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GASKET_STATUS_DEAD ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gasket_interrupt_cleanup (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_page_table_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  gasket_page_table_reset (scalar_t__) ; 

void gasket_disable_device(struct gasket_dev *gasket_dev)
{
	const struct gasket_driver_desc *driver_desc =
		gasket_dev->internal_desc->driver_desc;
	int i;

	/* Only delete the device if it has been successfully added. */
	if (gasket_dev->dev_info.cdev_added)
		cdev_del(&gasket_dev->dev_info.cdev);

	gasket_dev->status = GASKET_STATUS_DEAD;

	gasket_interrupt_cleanup(gasket_dev);

	for (i = 0; i < driver_desc->num_page_tables; ++i) {
		if (gasket_dev->page_table[i]) {
			gasket_page_table_reset(gasket_dev->page_table[i]);
			gasket_page_table_cleanup(gasket_dev->page_table[i]);
		}
	}
}