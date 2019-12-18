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
struct usb_device {int quirks; } ;
struct usb_ctrlrequest {void* wLength; void* wIndex; void* wValue; void* bRequest; void* bRequestType; } ;
typedef  void* __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int USB_QUIRK_DELAY_CTRL_MSG ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usb_ctrlrequest*) ; 
 struct usb_ctrlrequest* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_internal_control_msg (struct usb_device*,unsigned int,struct usb_ctrlrequest*,void*,int /*<<< orphan*/ ,int) ; 

int usb_control_msg(struct usb_device *dev, unsigned int pipe, __u8 request,
		    __u8 requesttype, __u16 value, __u16 index, void *data,
		    __u16 size, int timeout)
{
	struct usb_ctrlrequest *dr;
	int ret;

	dr = kmalloc(sizeof(struct usb_ctrlrequest), GFP_NOIO);
	if (!dr)
		return -ENOMEM;

	dr->bRequestType = requesttype;
	dr->bRequest = request;
	dr->wValue = cpu_to_le16(value);
	dr->wIndex = cpu_to_le16(index);
	dr->wLength = cpu_to_le16(size);

	ret = usb_internal_control_msg(dev, pipe, dr, data, size, timeout);

	/* Linger a bit, prior to the next control message. */
	if (dev->quirks & USB_QUIRK_DELAY_CTRL_MSG)
		msleep(200);

	kfree(dr);

	return ret;
}