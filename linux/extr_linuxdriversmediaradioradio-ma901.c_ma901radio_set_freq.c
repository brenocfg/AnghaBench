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
struct ma901radio_device {int* buffer; int curfreq; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int MA901_RADIO_SET_FREQ ; 
 int /*<<< orphan*/  USB_TIMEOUT ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ma901radio_set_freq(struct ma901radio_device *radio, int freq)
{
	unsigned int freq_send = 0x300 + (freq >> 5) / 25;
	int retval;

	radio->buffer[0] = 0x0a;
	radio->buffer[1] = MA901_RADIO_SET_FREQ;
	radio->buffer[2] = ((freq_send >> 8) & 0xff) + 0x80;
	radio->buffer[3] = freq_send & 0xff;
	radio->buffer[4] = 0x00;
	radio->buffer[5] = 0x00;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);
	if (retval < 0)
		return retval;

	radio->curfreq = freq;
	return 0;
}