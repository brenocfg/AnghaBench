#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct usb_request {scalar_t__ length; scalar_t__ buf; int /*<<< orphan*/ * context; } ;
struct usb_function {int dummy; } ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; } ;
struct fsg_dev {int interface_number; TYPE_1__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  ep0_req_tag; struct usb_request* ep0req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int EDOM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FSG_STATE_PROTOCOL_RESET ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_GADGET_DELAYED_STATUS ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
#define  US_BULK_GET_MAX_LUN 129 
#define  US_BULK_RESET_REQUEST 128 
 int /*<<< orphan*/  VDBG (struct fsg_dev*,char*,...) ; 
 int /*<<< orphan*/  _fsg_common_get_max_lun (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_msg (struct fsg_dev*,char*,int /*<<< orphan*/ *,int) ; 
 int ep0_queue (TYPE_1__*) ; 
 struct fsg_dev* fsg_from_func (struct usb_function*) ; 
 int /*<<< orphan*/  fsg_is_set (TYPE_1__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,int) ; 
 int /*<<< orphan*/  raise_exception (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsg_setup(struct usb_function *f,
		     const struct usb_ctrlrequest *ctrl)
{
	struct fsg_dev		*fsg = fsg_from_func(f);
	struct usb_request	*req = fsg->common->ep0req;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	if (!fsg_is_set(fsg->common))
		return -EOPNOTSUPP;

	++fsg->common->ep0_req_tag;	/* Record arrival of a new request */
	req->context = NULL;
	req->length = 0;
	dump_msg(fsg, "ep0-setup", (u8 *) ctrl, sizeof(*ctrl));

	switch (ctrl->bRequest) {

	case US_BULK_RESET_REQUEST:
		if (ctrl->bRequestType !=
		    (USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE))
			break;
		if (w_index != fsg->interface_number || w_value != 0 ||
				w_length != 0)
			return -EDOM;

		/*
		 * Raise an exception to stop the current operation
		 * and reinitialize our state.
		 */
		DBG(fsg, "bulk reset request\n");
		raise_exception(fsg->common, FSG_STATE_PROTOCOL_RESET);
		return USB_GADGET_DELAYED_STATUS;

	case US_BULK_GET_MAX_LUN:
		if (ctrl->bRequestType !=
		    (USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE))
			break;
		if (w_index != fsg->interface_number || w_value != 0 ||
				w_length != 1)
			return -EDOM;
		VDBG(fsg, "get max LUN\n");
		*(u8 *)req->buf = _fsg_common_get_max_lun(fsg->common);

		/* Respond with data/status */
		req->length = min((u16)1, w_length);
		return ep0_queue(fsg->common);
	}

	VDBG(fsg,
	     "unknown class-specific control req %02x.%02x v%04x i%04x l%u\n",
	     ctrl->bRequestType, ctrl->bRequest,
	     le16_to_cpu(ctrl->wValue), w_index, w_length);
	return -EOPNOTSUPP;
}