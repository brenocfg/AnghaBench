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
typedef  size_t u8 ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wIndex; } ;
struct TYPE_2__ {int length; int /*<<< orphan*/ * complete; scalar_t__ actual; int /*<<< orphan*/ * buf; } ;
struct s3c_hsudc_req {TYPE_1__ req; int /*<<< orphan*/  queue; } ;
struct s3c_hsudc_ep {int /*<<< orphan*/  stopped; } ;
struct s3c_hsudc {struct s3c_hsudc_ep* ep; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hsudc_write_fifo (struct s3c_hsudc_ep*,struct s3c_hsudc_req*) ; 

__attribute__((used)) static void s3c_hsudc_process_req_status(struct s3c_hsudc *hsudc,
					struct usb_ctrlrequest *ctrl)
{
	struct s3c_hsudc_ep *hsep0 = &hsudc->ep[0];
	struct s3c_hsudc_req hsreq;
	struct s3c_hsudc_ep *hsep;
	__le16 reply;
	u8 epnum;

	switch (ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		reply = cpu_to_le16(0);
		break;

	case USB_RECIP_INTERFACE:
		reply = cpu_to_le16(0);
		break;

	case USB_RECIP_ENDPOINT:
		epnum = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		hsep = &hsudc->ep[epnum];
		reply = cpu_to_le16(hsep->stopped ? 1 : 0);
		break;
	}

	INIT_LIST_HEAD(&hsreq.queue);
	hsreq.req.length = 2;
	hsreq.req.buf = &reply;
	hsreq.req.actual = 0;
	hsreq.req.complete = NULL;
	s3c_hsudc_write_fifo(hsep0, &hsreq);
}