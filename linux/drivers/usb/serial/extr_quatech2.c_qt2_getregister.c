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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QT2_USB_TIMEOUT ; 
 int /*<<< orphan*/  QT_SET_GET_REGISTER ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qt2_getregister(struct usb_device *dev,
				  u8 uart,
				  u8 reg,
				  u8 *data)
{
	int ret;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      QT_SET_GET_REGISTER, 0xc0, reg,
			      uart, data, sizeof(*data), QT2_USB_TIMEOUT);
	if (ret < (int)sizeof(*data)) {
		if (ret >= 0)
			ret = -EIO;
	}

	return ret;
}