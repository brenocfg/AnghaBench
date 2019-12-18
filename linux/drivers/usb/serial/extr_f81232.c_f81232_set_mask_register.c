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
typedef  int /*<<< orphan*/  u16 ;
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 int f81232_get_register (struct usb_serial_port*,int /*<<< orphan*/ ,int*) ; 
 int f81232_set_register (struct usb_serial_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int f81232_set_mask_register(struct usb_serial_port *port, u16 reg,
					u8 mask, u8 val)
{
	int status;
	u8 tmp;

	status = f81232_get_register(port, reg, &tmp);
	if (status)
		return status;

	tmp = (tmp & ~mask) | (val & mask);

	return f81232_set_register(port, reg, tmp);
}