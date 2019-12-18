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
struct usb_request {scalar_t__ actual; scalar_t__ length; int /*<<< orphan*/  buf; scalar_t__ status; struct usb_function* context; } ;
struct usb_function {TYPE_1__* config; } ;
struct usb_ep {int dummy; } ;
struct usb_composite_dev {int dummy; } ;
struct TYPE_5__ {unsigned int fixed_in_len; } ;
struct f_ncm {TYPE_2__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwNtbInMaxSize; } ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,...) ; 
 unsigned int USB_CDC_NCM_NTB_MIN_IN_SIZE ; 
 int /*<<< orphan*/  VDBG (struct usb_composite_dev*,char*,unsigned int) ; 
 struct f_ncm* func_to_ncm (struct usb_function*) ; 
 unsigned int get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__ ntb_parameters ; 
 int /*<<< orphan*/  usb_ep_set_halt (struct usb_ep*) ; 

__attribute__((used)) static void ncm_ep0out_complete(struct usb_ep *ep, struct usb_request *req)
{
	/* now for SET_NTB_INPUT_SIZE only */
	unsigned		in_size;
	struct usb_function	*f = req->context;
	struct f_ncm		*ncm = func_to_ncm(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	req->context = NULL;
	if (req->status || req->actual != req->length) {
		DBG(cdev, "Bad control-OUT transfer\n");
		goto invalid;
	}

	in_size = get_unaligned_le32(req->buf);
	if (in_size < USB_CDC_NCM_NTB_MIN_IN_SIZE ||
	    in_size > le32_to_cpu(ntb_parameters.dwNtbInMaxSize)) {
		DBG(cdev, "Got wrong INPUT SIZE (%d) from host\n", in_size);
		goto invalid;
	}

	ncm->port.fixed_in_len = in_size;
	VDBG(cdev, "Set NTB INPUT SIZE %d\n", in_size);
	return;

invalid:
	usb_ep_set_halt(ep);
	return;
}