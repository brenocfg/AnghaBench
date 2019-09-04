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
struct ma901radio_device {int* buffer; int /*<<< orphan*/  stereo; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LENGTH ; 
 int MA901_RADIO_SET_MONO_STEREO ; 
 int MA901_WANT_STEREO ; 
 int /*<<< orphan*/  USB_TIMEOUT ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ma901_set_stereo(struct ma901radio_device *radio, u8 stereo)
{
	int retval;

	radio->buffer[0] = 0x0a;
	radio->buffer[1] = MA901_RADIO_SET_MONO_STEREO;
	radio->buffer[2] = stereo;
	radio->buffer[3] = 0x00;
	radio->buffer[4] = 0x00;
	radio->buffer[5] = 0x00;
	radio->buffer[6] = 0x00;
	radio->buffer[7] = 0x00;

	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
				9, 0x21, 0x0300, 0,
				radio->buffer, BUFFER_LENGTH, USB_TIMEOUT);

	if (retval < 0)
		return retval;

	if (stereo == MA901_WANT_STEREO)
		radio->stereo = V4L2_TUNER_MODE_STEREO;
	else
		radio->stereo = V4L2_TUNER_MODE_MONO;

	return retval;
}