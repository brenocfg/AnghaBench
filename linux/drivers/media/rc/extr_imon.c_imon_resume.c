#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct imon_context {int /*<<< orphan*/  rx_urb_intf1; TYPE_4__* rx_endpoint_intf1; int /*<<< orphan*/  usb_rx_buf; int /*<<< orphan*/  usbdev_intf1; int /*<<< orphan*/  rx_urb_intf0; TYPE_3__* rx_endpoint_intf0; int /*<<< orphan*/  usbdev_intf0; } ;
struct TYPE_8__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_7__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_5__ {int bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct imon_context*,int /*<<< orphan*/ ) ; 
 struct imon_context* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rx_callback_intf0 ; 
 int /*<<< orphan*/  usb_rx_callback_intf1 ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imon_resume(struct usb_interface *intf)
{
	int rc = 0;
	struct imon_context *ictx = usb_get_intfdata(intf);
	int ifnum = intf->cur_altsetting->desc.bInterfaceNumber;

	if (ifnum == 0) {
		usb_fill_int_urb(ictx->rx_urb_intf0, ictx->usbdev_intf0,
			usb_rcvintpipe(ictx->usbdev_intf0,
				ictx->rx_endpoint_intf0->bEndpointAddress),
			ictx->usb_rx_buf, sizeof(ictx->usb_rx_buf),
			usb_rx_callback_intf0, ictx,
			ictx->rx_endpoint_intf0->bInterval);

		rc = usb_submit_urb(ictx->rx_urb_intf0, GFP_ATOMIC);

	} else {
		usb_fill_int_urb(ictx->rx_urb_intf1, ictx->usbdev_intf1,
			usb_rcvintpipe(ictx->usbdev_intf1,
				ictx->rx_endpoint_intf1->bEndpointAddress),
			ictx->usb_rx_buf, sizeof(ictx->usb_rx_buf),
			usb_rx_callback_intf1, ictx,
			ictx->rx_endpoint_intf1->bInterval);

		rc = usb_submit_urb(ictx->rx_urb_intf1, GFP_ATOMIC);
	}

	return rc;
}