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
struct mt76_usb {int /*<<< orphan*/ * out_ep; int /*<<< orphan*/ * in_ep; } ;
struct mt76_dev {struct mt76_usb usb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t MT_EP_IN_CMD_RESP ; 
 size_t MT_EP_OUT_INBAND_CMD ; 
 struct usb_device* to_usb_device (int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,unsigned int,void*,int,int*,int) ; 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
mt76u_bulk_msg(struct mt76_dev *dev, void *data, int len, int *actual_len,
	       int timeout)
{
	struct usb_device *udev = to_usb_device(dev->dev);
	struct mt76_usb *usb = &dev->usb;
	unsigned int pipe;

	if (actual_len)
		pipe = usb_rcvbulkpipe(udev, usb->in_ep[MT_EP_IN_CMD_RESP]);
	else
		pipe = usb_sndbulkpipe(udev, usb->out_ep[MT_EP_OUT_INBAND_CMD]);

	return usb_bulk_msg(udev, pipe, data, len, actual_len, timeout);
}