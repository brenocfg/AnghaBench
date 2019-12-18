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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct usb_serial_port {int /*<<< orphan*/  serial; } ;
struct f81534_port_private {int phy_num; } ;

/* Variables and functions */
 int F81534_UART_OFFSET ; 
 int f81534_get_register (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct f81534_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int f81534_get_port_register(struct usb_serial_port *port, u16 reg,
					u8 *data)
{
	struct f81534_port_private *port_priv = usb_get_serial_port_data(port);

	return f81534_get_register(port->serial,
			reg + port_priv->phy_num * F81534_UART_OFFSET, data);
}