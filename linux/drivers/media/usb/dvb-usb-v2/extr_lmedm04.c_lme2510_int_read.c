#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct lme2510_state {TYPE_1__* lme_urb; int /*<<< orphan*/  int_buffer; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;
struct dvb_usb_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ USB_ENDPOINT_XFER_BULK ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct lme2510_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  lme2510_int_response ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dvb_usb_adapter*,int) ; 
 struct usb_host_endpoint* usb_pipe_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lme2510_int_read(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct lme2510_state *lme_int = adap_to_priv(adap);
	struct usb_host_endpoint *ep;

	lme_int->lme_urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (lme_int->lme_urb == NULL)
			return -ENOMEM;

	usb_fill_int_urb(lme_int->lme_urb,
			 d->udev,
			 usb_rcvintpipe(d->udev, 0xa),
			 lme_int->int_buffer,
			 sizeof(lme_int->int_buffer),
			 lme2510_int_response,
			 adap,
			 8);

	/* Quirk of pipe reporting PIPE_BULK but behaves as interrupt */
	ep = usb_pipe_endpoint(d->udev, lme_int->lme_urb->pipe);

	if (usb_endpoint_type(&ep->desc) == USB_ENDPOINT_XFER_BULK)
		lme_int->lme_urb->pipe = usb_rcvbulkpipe(d->udev, 0xa),

	usb_submit_urb(lme_int->lme_urb, GFP_ATOMIC);
	info("INT Interrupt Service Started");

	return 0;
}