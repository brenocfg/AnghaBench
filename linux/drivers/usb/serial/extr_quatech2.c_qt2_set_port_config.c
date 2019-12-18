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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT2_GET_SET_UART ; 
 int /*<<< orphan*/  QT2_USB_TIMEOUT ; 
 int calc_baud_divisor (int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qt2_set_port_config(struct usb_device *dev,
				      unsigned char port_number,
				      u16 baudrate, u16 lcr)
{
	int divisor = calc_baud_divisor(baudrate);
	u16 index = ((u16) (lcr << 8) | (u16) (port_number));

	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       QT2_GET_SET_UART, 0x40,
			       divisor, index, NULL, 0, QT2_USB_TIMEOUT);
}