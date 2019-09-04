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
struct si4713_usb_device {int* buffer; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int EIO ; 
 int SI4713_CTS ; 
 int /*<<< orphan*/  USB_RESP_TIMEOUT ; 
 int /*<<< orphan*/  USB_TIMEOUT ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_send_startup_command(struct si4713_usb_device *radio)
{
	unsigned long until_jiffies = jiffies + usecs_to_jiffies(USB_RESP_TIMEOUT) + 1;
	u8 *buffer = radio->buffer;
	int retval;

	/* send the command */
	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
					0x09, 0x21, 0x033f, 0, radio->buffer,
					BUFFER_LENGTH, USB_TIMEOUT);
	if (retval < 0)
		return retval;

	for (;;) {
		/* receive the response */
		retval = usb_control_msg(radio->usbdev, usb_rcvctrlpipe(radio->usbdev, 0),
				0x01, 0xa1, 0x033f, 0, radio->buffer,
				BUFFER_LENGTH, USB_TIMEOUT);
		if (retval < 0)
			return retval;
		if (!radio->buffer[1]) {
			/* USB traffic sniffing showed that some commands require
			 * additional checks. */
			switch (buffer[1]) {
			case 0x32:
				if (radio->buffer[2] == 0)
					return 0;
				break;
			case 0x14:
			case 0x12:
				if (radio->buffer[2] & SI4713_CTS)
					return 0;
				break;
			case 0x06:
				if ((radio->buffer[2] & SI4713_CTS) && radio->buffer[9] == 0x08)
					return 0;
				break;
			default:
				return 0;
			}
		}
		if (time_is_before_jiffies(until_jiffies))
			return -EIO;
		msleep(3);
	}

	return retval;
}