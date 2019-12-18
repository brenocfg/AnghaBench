#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_3__* altsetting; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct urb {int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/  status; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; struct dib0700_state* priv; } ;
struct dib0700_state {int fw_version; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct TYPE_6__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RC_MSG_SIZE_V1_20 ; 
 int /*<<< orphan*/  dib0700_rc_urb_completion ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_xfer_int (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_usb_device*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_usb_device*,int) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 unsigned int usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 unsigned int usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int dib0700_rc_setup(struct dvb_usb_device *d, struct usb_interface *intf)
{
	struct dib0700_state *st = d->priv;
	struct urb *purb;
	const struct usb_endpoint_descriptor *e;
	int ret, rc_ep = 1;
	unsigned int pipe = 0;

	/* Poll-based. Don't initialize bulk mode */
	if (st->fw_version < 0x10200 || !intf)
		return 0;

	/* Starting in firmware 1.20, the RC info is provided on a bulk pipe */

	if (intf->altsetting[0].desc.bNumEndpoints < rc_ep + 1)
		return -ENODEV;

	purb = usb_alloc_urb(0, GFP_KERNEL);
	if (purb == NULL)
		return -ENOMEM;

	purb->transfer_buffer = kzalloc(RC_MSG_SIZE_V1_20, GFP_KERNEL);
	if (purb->transfer_buffer == NULL) {
		err("rc kzalloc failed");
		usb_free_urb(purb);
		return -ENOMEM;
	}

	purb->status = -EINPROGRESS;

	/*
	 * Some devices like the Hauppauge NovaTD model 52009 use an interrupt
	 * endpoint, while others use a bulk one.
	 */
	e = &intf->altsetting[0].endpoint[rc_ep].desc;
	if (usb_endpoint_dir_in(e)) {
		if (usb_endpoint_xfer_bulk(e)) {
			pipe = usb_rcvbulkpipe(d->udev, rc_ep);
			usb_fill_bulk_urb(purb, d->udev, pipe,
					  purb->transfer_buffer,
					  RC_MSG_SIZE_V1_20,
					  dib0700_rc_urb_completion, d);

		} else if (usb_endpoint_xfer_int(e)) {
			pipe = usb_rcvintpipe(d->udev, rc_ep);
			usb_fill_int_urb(purb, d->udev, pipe,
					  purb->transfer_buffer,
					  RC_MSG_SIZE_V1_20,
					  dib0700_rc_urb_completion, d, 1);
		}
	}

	if (!pipe) {
		err("There's no endpoint for remote controller");
		kfree(purb->transfer_buffer);
		usb_free_urb(purb);
		return 0;
	}

	ret = usb_submit_urb(purb, GFP_ATOMIC);
	if (ret) {
		err("rc submit urb failed");
		kfree(purb->transfer_buffer);
		usb_free_urb(purb);
	}

	return ret;
}