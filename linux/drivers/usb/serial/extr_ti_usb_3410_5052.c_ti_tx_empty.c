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
typedef  int u8 ;
struct usb_serial_port {int dummy; } ;
struct ti_port {int dummy; } ;

/* Variables and functions */
 int TI_LSR_TX_EMPTY ; 
 int ti_get_lsr (struct ti_port*,int*) ; 
 struct ti_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static bool ti_tx_empty(struct usb_serial_port *port)
{
	struct ti_port *tport = usb_get_serial_port_data(port);
	int ret;
	u8 lsr;

	ret = ti_get_lsr(tport, &lsr);
	if (!ret && !(lsr & TI_LSR_TX_EMPTY))
		return false;

	return true;
}