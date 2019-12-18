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
 int /*<<< orphan*/  HUB_CLEAR_TT_BUFFER ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_CONTROL ; 
 int /*<<< orphan*/  USB_RT_PORT ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
hub_clear_tt_buffer(struct usb_device *hdev, u16 devinfo, u16 tt)
{
	/* Need to clear both directions for control ep */
	if (((devinfo >> 11) & USB_ENDPOINT_XFERTYPE_MASK) ==
			USB_ENDPOINT_XFER_CONTROL) {
		int status = usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
				HUB_CLEAR_TT_BUFFER, USB_RT_PORT,
				devinfo ^ 0x8000, tt, NULL, 0, 1000);
		if (status)
			return status;
	}
	return usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
			       HUB_CLEAR_TT_BUFFER, USB_RT_PORT, devinfo,
			       tt, NULL, 0, 1000);
}