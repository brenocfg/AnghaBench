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
struct usb_driver {int dummy; } ;
struct comedi_driver {int dummy; } ;

/* Variables and functions */
 int comedi_driver_register (struct comedi_driver*) ; 
 int /*<<< orphan*/  comedi_driver_unregister (struct comedi_driver*) ; 
 int usb_register (struct usb_driver*) ; 

int comedi_usb_driver_register(struct comedi_driver *comedi_driver,
			       struct usb_driver *usb_driver)
{
	int ret;

	ret = comedi_driver_register(comedi_driver);
	if (ret < 0)
		return ret;

	ret = usb_register(usb_driver);
	if (ret < 0) {
		comedi_driver_unregister(comedi_driver);
		return ret;
	}

	return 0;
}