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
struct usb_hcd {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* find_raw_port_number ) (struct usb_hcd*,int) ;} ;

/* Variables and functions */
 int stub1 (struct usb_hcd*,int) ; 

int usb_hcd_find_raw_port_number(struct usb_hcd *hcd, int port1)
{
	if (!hcd->driver->find_raw_port_number)
		return port1;

	return hcd->driver->find_raw_port_number(hcd, port1);
}