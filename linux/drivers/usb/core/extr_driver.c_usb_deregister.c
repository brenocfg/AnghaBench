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
struct usb_driver {TYPE_1__ drvwrap; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_dynids (struct usb_driver*) ; 
 int /*<<< orphan*/  usb_remove_newid_files (struct usb_driver*) ; 
 int /*<<< orphan*/  usbcore_name ; 

void usb_deregister(struct usb_driver *driver)
{
	pr_info("%s: deregistering interface driver %s\n",
			usbcore_name, driver->name);

	usb_remove_newid_files(driver);
	driver_unregister(&driver->drvwrap.driver);
	usb_free_dynids(driver);
}