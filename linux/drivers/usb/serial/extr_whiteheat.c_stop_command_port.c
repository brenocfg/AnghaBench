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
struct whiteheat_command_private {int /*<<< orphan*/  mutex; int /*<<< orphan*/  port_running; } ;
struct usb_serial_port {int /*<<< orphan*/  read_urb; } ;
struct usb_serial {struct usb_serial_port** port; } ;

/* Variables and functions */
 size_t COMMAND_PORT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct whiteheat_command_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_command_port(struct usb_serial *serial)
{
	struct usb_serial_port *command_port;
	struct whiteheat_command_private *command_info;

	command_port = serial->port[COMMAND_PORT];
	command_info = usb_get_serial_port_data(command_port);
	mutex_lock(&command_info->mutex);
	command_info->port_running--;
	if (!command_info->port_running)
		usb_kill_urb(command_port->read_urb);
	mutex_unlock(&command_info->mutex);
}