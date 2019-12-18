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
struct whiteheat_purge {int /*<<< orphan*/  what; scalar_t__ port; } ;
struct usb_serial_port {scalar_t__ port_number; } ;
typedef  int /*<<< orphan*/  purge_command ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WHITEHEAT_PURGE ; 
 int firm_send_command (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int firm_purge(struct usb_serial_port *port, __u8 rxtx)
{
	struct whiteheat_purge purge_command;

	purge_command.port = port->port_number + 1;
	purge_command.what = rxtx;
	return firm_send_command(port, WHITEHEAT_PURGE,
			(__u8 *)&purge_command, sizeof(purge_command));
}