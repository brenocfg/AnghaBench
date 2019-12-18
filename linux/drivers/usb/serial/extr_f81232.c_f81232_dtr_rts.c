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

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  f81232_set_mctrl (struct usb_serial_port*,int,int) ; 

__attribute__((used)) static void f81232_dtr_rts(struct usb_serial_port *port, int on)
{
	if (on)
		f81232_set_mctrl(port, TIOCM_DTR | TIOCM_RTS, 0);
	else
		f81232_set_mctrl(port, 0, TIOCM_DTR | TIOCM_RTS);
}