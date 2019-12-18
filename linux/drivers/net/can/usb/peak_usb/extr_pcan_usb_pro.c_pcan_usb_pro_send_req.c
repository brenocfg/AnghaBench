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
struct peak_usb_device {int state; int /*<<< orphan*/  netdev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
#define  PCAN_USBPRO_REQ_FCT 128 
 int PCAN_USB_STATE_CONNECTED ; 
 int USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_OTHER ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  memset (void*,char,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,int,int /*<<< orphan*/ ,void*,int,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcan_usb_pro_send_req(struct peak_usb_device *dev, int req_id,
			  int req_value, void *req_addr, int req_size)
{
	int err;
	u8 req_type;
	unsigned int p;

	/* usb device unregistered? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		return 0;

	req_type = USB_TYPE_VENDOR | USB_RECIP_OTHER;

	switch (req_id) {
	case PCAN_USBPRO_REQ_FCT:
		p = usb_sndctrlpipe(dev->udev, 0);
		break;

	default:
		p = usb_rcvctrlpipe(dev->udev, 0);
		req_type |= USB_DIR_IN;
		memset(req_addr, '\0', req_size);
		break;
	}

	err = usb_control_msg(dev->udev, p, req_id, req_type, req_value, 0,
			      req_addr, req_size, 2 * USB_CTRL_GET_TIMEOUT);
	if (err < 0) {
		netdev_info(dev->netdev,
			    "unable to request usb[type=%d value=%d] err=%d\n",
			    req_id, req_value, err);
		return err;
	}

	return 0;
}