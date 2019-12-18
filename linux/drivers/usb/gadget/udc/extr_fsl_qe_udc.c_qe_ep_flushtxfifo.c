#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qe_udc {TYPE_2__** ep_param; TYPE_1__* usb_regs; } ;
struct qe_ep {int epnum; int /*<<< orphan*/  txbase; int /*<<< orphan*/  n_txbd; int /*<<< orphan*/  c_txbd; struct qe_udc* udc; } ;
struct TYPE_4__ {int /*<<< orphan*/  tbcnt; int /*<<< orphan*/  tstate; int /*<<< orphan*/  tbase; int /*<<< orphan*/  tbptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_uscom; } ;

/* Variables and functions */
 int USB_CMD_EP_MASK ; 
 int USB_CMD_FLUSH_FIFO ; 
 int /*<<< orphan*/  in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep_cmd_restarttx (struct qe_ep*) ; 
 int /*<<< orphan*/  qe_ep_cmd_stoptx (struct qe_ep*) ; 

__attribute__((used)) static int qe_ep_flushtxfifo(struct qe_ep *ep)
{
	struct qe_udc *udc = ep->udc;
	int i;

	i = (int)ep->epnum;

	qe_ep_cmd_stoptx(ep);
	out_8(&udc->usb_regs->usb_uscom,
		USB_CMD_FLUSH_FIFO | (USB_CMD_EP_MASK & (ep->epnum)));
	out_be16(&udc->ep_param[i]->tbptr, in_be16(&udc->ep_param[i]->tbase));
	out_be32(&udc->ep_param[i]->tstate, 0);
	out_be16(&udc->ep_param[i]->tbcnt, 0);

	ep->c_txbd = ep->txbase;
	ep->n_txbd = ep->txbase;
	qe_ep_cmd_restarttx(ep);
	return 0;
}