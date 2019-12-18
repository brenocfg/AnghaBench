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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_driver {TYPE_1__ drvwrap; int /*<<< orphan*/ * probe; scalar_t__ no_dynamic_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_new_id ; 
 int /*<<< orphan*/  driver_attr_remove_id ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_remove_newid_files(struct usb_driver *usb_drv)
{
	if (usb_drv->no_dynamic_id)
		return;

	if (usb_drv->probe != NULL) {
		driver_remove_file(&usb_drv->drvwrap.driver,
				&driver_attr_remove_id);
		driver_remove_file(&usb_drv->drvwrap.driver,
				   &driver_attr_new_id);
	}
}