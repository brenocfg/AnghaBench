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
typedef  int u16 ;
struct usb_serial_port {int dummy; } ;
struct cp210x_port_private {int has_swapped_line_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP210X_GET_LINE_CTL ; 
 int /*<<< orphan*/  CP210X_SET_LINE_CTL ; 
 int cp210x_read_u16_reg (struct usb_serial_port*,int /*<<< orphan*/ ,int*) ; 
 int cp210x_write_u16_reg (struct usb_serial_port*,int /*<<< orphan*/ ,int) ; 
 int swab16 (int) ; 
 struct cp210x_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int cp210x_detect_swapped_line_ctl(struct usb_serial_port *port)
{
	struct cp210x_port_private *port_priv = usb_get_serial_port_data(port);
	u16 line_ctl_save;
	u16 line_ctl_test;
	int err;

	err = cp210x_read_u16_reg(port, CP210X_GET_LINE_CTL, &line_ctl_save);
	if (err)
		return err;

	err = cp210x_write_u16_reg(port, CP210X_SET_LINE_CTL, 0x800);
	if (err)
		return err;

	err = cp210x_read_u16_reg(port, CP210X_GET_LINE_CTL, &line_ctl_test);
	if (err)
		return err;

	if (line_ctl_test == 8) {
		port_priv->has_swapped_line_ctl = true;
		line_ctl_save = swab16(line_ctl_save);
	}

	return cp210x_write_u16_reg(port, CP210X_SET_LINE_CTL, line_ctl_save);
}