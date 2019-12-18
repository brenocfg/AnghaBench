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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 scalar_t__ mos7840_port_paranoia_check (struct usb_serial_port*,char const*) ; 
 scalar_t__ mos7840_serial_paranoia_check (struct usb_serial*,char const*) ; 

__attribute__((used)) static struct usb_serial *mos7840_get_usb_serial(struct usb_serial_port *port,
						 const char *function)
{
	/* if no port was specified, or it fails a paranoia check */
	if (!port ||
	    mos7840_port_paranoia_check(port, function) ||
	    mos7840_serial_paranoia_check(port->serial, function)) {
		/* then say that we don't have a valid usb_serial thing,
		 * which will end up genrating -ENODEV return values */
		return NULL;
	}

	return port->serial;
}