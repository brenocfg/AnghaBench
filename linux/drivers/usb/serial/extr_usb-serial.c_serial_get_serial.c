#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {TYPE_2__* serial; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int (* get_serial ) (struct tty_struct*,struct serial_struct*) ;} ;

/* Variables and functions */
 int ENOTTY ; 
 int stub1 (struct tty_struct*,struct serial_struct*) ; 

__attribute__((used)) static int serial_get_serial(struct tty_struct *tty, struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;

	if (port->serial->type->get_serial)
		return port->serial->type->get_serial(tty, ss);
	return -ENOTTY;
}