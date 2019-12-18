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
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct garmin_data {int outsize; } ;

/* Variables and functions */
 int GPS_OUT_BUFSIZ ; 
 struct garmin_data* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int garmin_write_room(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	/*
	 * Report back the bytes currently available in the output buffer.
	 */
	struct garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	return GPS_OUT_BUFSIZ-garmin_data_p->outsize;
}