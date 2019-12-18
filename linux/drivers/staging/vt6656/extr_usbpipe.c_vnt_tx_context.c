#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnt_usb_send_context {int in_use; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  data; struct urb* urb; } ;
struct vnt_private {TYPE_1__* usb; int /*<<< orphan*/  flags; } ;
struct urb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_FLAGS_DISCONNECTED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int STATUS_FAILURE ; 
 int STATUS_PENDING ; 
 int STATUS_RESOURCES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnt_usb_send_context*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_tx_context_complete ; 

int vnt_tx_context(struct vnt_private *priv,
		   struct vnt_usb_send_context *context)
{
	int status;
	struct urb *urb = context->urb;

	if (test_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags)) {
		context->in_use = false;
		return STATUS_RESOURCES;
	}

	usb_fill_bulk_urb(urb,
			  priv->usb,
			  usb_sndbulkpipe(priv->usb, 3),
			  context->data,
			  context->buf_len,
			  vnt_tx_context_complete,
			  context);

	status = usb_submit_urb(urb, GFP_ATOMIC);
	if (status) {
		dev_dbg(&priv->usb->dev, "Submit Tx URB failed %d\n", status);

		context->in_use = false;
		return STATUS_FAILURE;
	}

	return STATUS_PENDING;
}