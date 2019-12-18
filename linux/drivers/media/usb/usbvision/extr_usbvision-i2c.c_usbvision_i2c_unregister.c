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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct usb_usbvision {TYPE_1__ i2c_adap; scalar_t__ registered_i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_I2C ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_1__*) ; 

int usbvision_i2c_unregister(struct usb_usbvision *usbvision)
{
	if (!usbvision->registered_i2c)
		return 0;

	i2c_del_adapter(&(usbvision->i2c_adap));
	usbvision->registered_i2c = 0;

	PDEBUG(DBG_I2C, "i2c bus for %s unregistered", usbvision->i2c_adap.name);

	return 0;
}