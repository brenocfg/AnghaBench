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
struct whiteheat_set_rdb {int /*<<< orphan*/  state; scalar_t__ port; } ;
struct usb_serial_port {scalar_t__ port_number; } ;
typedef  int /*<<< orphan*/  dtr_command ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WHITEHEAT_SET_DTR ; 
 int firm_send_command (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int firm_set_dtr(struct usb_serial_port *port, __u8 onoff)
{
	struct whiteheat_set_rdb dtr_command;

	dtr_command.port = port->port_number + 1;
	dtr_command.state = onoff;
	return firm_send_command(port, WHITEHEAT_SET_DTR,
			(__u8 *)&dtr_command, sizeof(dtr_command));
}