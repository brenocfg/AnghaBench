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
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SWIMS_USB_REQUEST_SetNmea ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_TYPE_VENDOR ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sierra_vsc_set_nmea(struct usb_device *udev, __u16 enable)
{
	return usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			SWIMS_USB_REQUEST_SetNmea,	/* __u8 request      */
			USB_TYPE_VENDOR,		/* __u8 request type */
			enable,				/* __u16 value       */
			0x0000,				/* __u16 index       */
			NULL,				/* void *data        */
			0,				/* __u16 size 	     */
			USB_CTRL_SET_TIMEOUT);		/* int timeout       */
}