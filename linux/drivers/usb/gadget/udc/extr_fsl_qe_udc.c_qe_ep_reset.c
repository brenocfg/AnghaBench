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
typedef  int /*<<< orphan*/  u16 ;
struct qe_udc {TYPE_1__* usb_regs; struct qe_ep* eps; } ;
struct qe_ep {int dir; } ;
struct TYPE_2__ {int /*<<< orphan*/ * usb_usep; } ;

/* Variables and functions */
#define  USB_DIR_BOTH 130 
#define  USB_DIR_IN 129 
#define  USB_DIR_OUT 128 
 int /*<<< orphan*/  USB_RHS_IGNORE_OUT ; 
 int /*<<< orphan*/  USB_RTHS_MASK ; 
 int /*<<< orphan*/  USB_THS_IGNORE_IN ; 
 int /*<<< orphan*/  in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep_flushtxfifo (struct qe_ep*) ; 
 int /*<<< orphan*/  qe_epbds_reset (struct qe_udc*,int) ; 

__attribute__((used)) static int qe_ep_reset(struct qe_udc *udc, int pipe_num)
{
	struct qe_ep *ep;
	u16 tmpusep;

	ep = &udc->eps[pipe_num];
	tmpusep = in_be16(&udc->usb_regs->usb_usep[pipe_num]);
	tmpusep &= ~USB_RTHS_MASK;

	switch (ep->dir) {
	case USB_DIR_BOTH:
		qe_ep_flushtxfifo(ep);
		break;
	case USB_DIR_OUT:
		tmpusep |= USB_THS_IGNORE_IN;
		break;
	case USB_DIR_IN:
		qe_ep_flushtxfifo(ep);
		tmpusep |= USB_RHS_IGNORE_OUT;
		break;
	default:
		break;
	}
	out_be16(&udc->usb_regs->usb_usep[pipe_num], tmpusep);

	qe_epbds_reset(udc, pipe_num);

	return 0;
}