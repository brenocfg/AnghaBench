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
struct usbport_trig_data {int dummy; } ;
struct usb_device {int maxchild; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbport_trig_add_port (struct usbport_trig_data*,struct usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbport_trig_add_usb_dev_ports(struct usb_device *usb_dev,
					  void *data)
{
	struct usbport_trig_data *usbport_data = data;
	int i;

	for (i = 1; i <= usb_dev->maxchild; i++)
		usbport_trig_add_port(usbport_data, usb_dev,
				      dev_name(&usb_dev->dev), i);

	return 0;
}