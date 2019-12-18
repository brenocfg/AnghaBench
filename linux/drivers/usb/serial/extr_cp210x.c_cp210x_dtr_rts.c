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
 int /*<<< orphan*/  cp210x_tiocmset_port (struct usb_serial_port*,int,int) ; 

__attribute__((used)) static void cp210x_dtr_rts(struct usb_serial_port *p, int on)
{
	if (on)
		cp210x_tiocmset_port(p, TIOCM_DTR|TIOCM_RTS, 0);
	else
		cp210x_tiocmset_port(p, 0, TIOCM_DTR|TIOCM_RTS);
}