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
typedef  char u8 ;
struct si4713_usb_device {int* buffer; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int BUFFER_LENGTH ; 
 int /*<<< orphan*/  USB_TIMEOUT ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_command(struct si4713_usb_device *radio, u8 *payload, char *data, int len)
{
	int retval;

	radio->buffer[0] = 0x3f;
	radio->buffer[1] = 0x06;

	memcpy(radio->buffer + 2, payload, 3);
	memcpy(radio->buffer + 5, data, len);
	memset(radio->buffer + 5 + len, 0, BUFFER_LENGTH - 5 - len);

	/* send the command */
	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
					0x09, 0x21, 0x033f, 0, radio->buffer,
					BUFFER_LENGTH, USB_TIMEOUT);

	return retval < 0 ? retval : 0;
}