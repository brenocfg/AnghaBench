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
struct usb_driver {int /*<<< orphan*/  id_table; int /*<<< orphan*/  dynids; } ;
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct usb_driver* to_usb_driver (struct device_driver*) ; 
 int /*<<< orphan*/  usb_store_new_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device_driver*,char const*,size_t) ; 

__attribute__((used)) static ssize_t new_id_store(struct device_driver *driver,
			    const char *buf, size_t count)
{
	struct usb_driver *usb_drv = to_usb_driver(driver);

	return usb_store_new_id(&usb_drv->dynids, usb_drv->id_table, driver, buf, count);
}