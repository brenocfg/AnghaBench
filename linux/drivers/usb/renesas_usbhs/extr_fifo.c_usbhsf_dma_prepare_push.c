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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int length; int actual; int buf; int trans; TYPE_1__* handler; int /*<<< orphan*/  work; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int dummy; } ;
struct TYPE_2__ {int (* prepare ) (struct usbhs_pkt*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int USBHS_USB_DMAC_XFER_SIZE ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  has_usb_dmac ; 
 int /*<<< orphan*/  pio_dma_border ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int stub1 (struct usbhs_pkt*,int*) ; 
 TYPE_1__ usbhs_fifo_pio_push_handler ; 
 int usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbhs_pipe_is_busy (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_running (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_type_is (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbhsf_dma_map (struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_dma_xfer_preparing (struct usbhs_pkt*) ; 
 int usbhsf_fifo_select (struct usbhs_pipe*,struct usbhs_fifo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 struct usbhs_fifo* usbhsf_get_dma_fifo (struct usbhs_priv*,struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_tx_irq_ctrl (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfer_work ; 

__attribute__((used)) static int usbhsf_dma_prepare_push(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_fifo *fifo;
	int len = pkt->length - pkt->actual;
	int ret;
	uintptr_t align_mask;

	if (usbhs_pipe_is_busy(pipe))
		return 0;

	/* use PIO if packet is less than pio_dma_border or pipe is DCP */
	if ((len < usbhs_get_dparam(priv, pio_dma_border)) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC))
		goto usbhsf_pio_prepare_push;

	/* check data length if this driver don't use USB-DMAC */
	if (!usbhs_get_dparam(priv, has_usb_dmac) && len & 0x7)
		goto usbhsf_pio_prepare_push;

	/* check buffer alignment */
	align_mask = usbhs_get_dparam(priv, has_usb_dmac) ?
					USBHS_USB_DMAC_XFER_SIZE - 1 : 0x7;
	if ((uintptr_t)(pkt->buf + pkt->actual) & align_mask)
		goto usbhsf_pio_prepare_push;

	/* return at this time if the pipe is running */
	if (usbhs_pipe_is_running(pipe))
		return 0;

	/* get enable DMA fifo */
	fifo = usbhsf_get_dma_fifo(priv, pkt);
	if (!fifo)
		goto usbhsf_pio_prepare_push;

	ret = usbhsf_fifo_select(pipe, fifo, 0);
	if (ret < 0)
		goto usbhsf_pio_prepare_push;

	if (usbhsf_dma_map(pkt) < 0)
		goto usbhsf_pio_prepare_push_unselect;

	pkt->trans = len;

	usbhsf_tx_irq_ctrl(pipe, 0);
	/* FIXME: Workaound for usb dmac that driver can be used in atomic */
	if (usbhs_get_dparam(priv, has_usb_dmac)) {
		usbhsf_dma_xfer_preparing(pkt);
	} else {
		INIT_WORK(&pkt->work, xfer_work);
		schedule_work(&pkt->work);
	}

	return 0;

usbhsf_pio_prepare_push_unselect:
	usbhsf_fifo_unselect(pipe, fifo);
usbhsf_pio_prepare_push:
	/*
	 * change handler to PIO
	 */
	pkt->handler = &usbhs_fifo_pio_push_handler;

	return pkt->handler->prepare(pkt, is_done);
}