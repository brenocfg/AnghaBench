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
struct ast_vhub_dev {TYPE_1__* vhub; int /*<<< orphan*/  driver; int /*<<< orphan*/  gadget; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*) ; 
 int /*<<< orphan*/  ast_vhub_dev_disable (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  ast_vhub_dev_enable (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_udc_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ast_vhub_dev_reset(struct ast_vhub_dev *d)
{
	/* No driver, just disable the device and return */
	if (!d->driver) {
		ast_vhub_dev_disable(d);
		return;
	}

	/* If the port isn't enabled, just enable it */
	if (!d->enabled) {
		DDBG(d, "Reset of disabled device, enabling...\n");
		ast_vhub_dev_enable(d);
	} else {
		DDBG(d, "Reset of enabled device, resetting...\n");
		spin_unlock(&d->vhub->lock);
		usb_gadget_udc_reset(&d->gadget, d->driver);
		spin_lock(&d->vhub->lock);

		/*
		 * Disable and maybe re-enable HW, this will clear the address
		 * and speed setting.
		 */
		ast_vhub_dev_disable(d);
		ast_vhub_dev_enable(d);
	}
}