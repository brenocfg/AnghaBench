#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int GET_TIMEOUT ; 
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_GET_REPORT ; 
 int USB_TYPE_CLASS ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char,int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_get_report(struct usb_device *dev,
			  struct usb_host_interface *inter, unsigned char type,
			  unsigned char id, void *buf, int size)
{
	return usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			       USB_REQ_GET_REPORT,
			       USB_DIR_IN | USB_TYPE_CLASS |
			       USB_RECIP_INTERFACE, (type << 8) + id,
			       inter->desc.bInterfaceNumber, buf, size,
			       GET_TIMEOUT*HZ);
}