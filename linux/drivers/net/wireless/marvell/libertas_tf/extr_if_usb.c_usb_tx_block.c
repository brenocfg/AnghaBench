#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u8 ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct if_usb_card {TYPE_2__* udev; int /*<<< orphan*/  ep_out; struct urb* cmd_urb; struct urb* tx_urb; TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ surpriseremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LBTF_DEB_USB ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  if_usb_write_bulk_callback ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_usb2 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lbtf_deb_usbd (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct if_usb_card*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_tx_block(struct if_usb_card *cardp, uint8_t *payload,
			uint16_t nb, u8 data)
{
	int ret = -1;
	struct urb *urb;

	lbtf_deb_enter(LBTF_DEB_USB);
	/* check if device is removed */
	if (cardp->priv->surpriseremoved) {
		lbtf_deb_usbd(&cardp->udev->dev, "Device removed\n");
		goto tx_ret;
	}

	if (data)
		urb = cardp->tx_urb;
	else
		urb = cardp->cmd_urb;

	usb_fill_bulk_urb(urb, cardp->udev,
			  usb_sndbulkpipe(cardp->udev,
					  cardp->ep_out),
			  payload, nb, if_usb_write_bulk_callback, cardp);

	urb->transfer_flags |= URB_ZERO_PACKET;

	if (usb_submit_urb(urb, GFP_ATOMIC)) {
		lbtf_deb_usbd(&cardp->udev->dev,
			"usb_submit_urb failed: %d\n", ret);
		goto tx_ret;
	}

	lbtf_deb_usb2(&cardp->udev->dev, "usb_submit_urb success\n");

	ret = 0;

tx_ret:
	lbtf_deb_leave(LBTF_DEB_USB);
	return ret;
}