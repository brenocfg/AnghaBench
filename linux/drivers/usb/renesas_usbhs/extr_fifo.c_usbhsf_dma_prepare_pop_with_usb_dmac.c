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
struct usbhs_pkt {scalar_t__ length; scalar_t__ trans; TYPE_1__* handler; scalar_t__ buf; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int dummy; } ;
struct TYPE_2__ {int (* prepare ) (struct usbhs_pkt*,int*) ;} ;

/* Variables and functions */
 int USBHS_USB_DMAC_XFER_SIZE ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  pio_dma_border ; 
 int stub1 (struct usbhs_pkt*,int*) ; 
 TYPE_1__ usbhs_fifo_pio_pop_handler ; 
 scalar_t__ usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_pipe_config_change_bfre (struct usbhs_pipe*,int) ; 
 scalar_t__ usbhs_pipe_is_busy (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_running (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_type_is (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbhsf_dma_map (struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_dma_xfer_preparing (struct usbhs_pkt*) ; 
 int usbhsf_fifo_select (struct usbhs_pipe*,struct usbhs_fifo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 struct usbhs_fifo* usbhsf_get_dma_fifo (struct usbhs_priv*,struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_rx_irq_ctrl (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsf_dma_prepare_pop_with_usb_dmac(struct usbhs_pkt *pkt,
						int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_fifo *fifo;
	int ret;

	if (usbhs_pipe_is_busy(pipe))
		return 0;

	/* use PIO if packet is less than pio_dma_border or pipe is DCP */
	if ((pkt->length < usbhs_get_dparam(priv, pio_dma_border)) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC))
		goto usbhsf_pio_prepare_pop;

	fifo = usbhsf_get_dma_fifo(priv, pkt);
	if (!fifo)
		goto usbhsf_pio_prepare_pop;

	if ((uintptr_t)pkt->buf & (USBHS_USB_DMAC_XFER_SIZE - 1))
		goto usbhsf_pio_prepare_pop;

	/* return at this time if the pipe is running */
	if (usbhs_pipe_is_running(pipe))
		return 0;

	usbhs_pipe_config_change_bfre(pipe, 1);

	ret = usbhsf_fifo_select(pipe, fifo, 0);
	if (ret < 0)
		goto usbhsf_pio_prepare_pop;

	if (usbhsf_dma_map(pkt) < 0)
		goto usbhsf_pio_prepare_pop_unselect;

	/* DMA */

	/*
	 * usbhs_fifo_dma_pop_handler :: prepare
	 * enabled irq to come here.
	 * but it is no longer needed for DMA. disable it.
	 */
	usbhsf_rx_irq_ctrl(pipe, 0);

	pkt->trans = pkt->length;

	usbhsf_dma_xfer_preparing(pkt);

	return 0;

usbhsf_pio_prepare_pop_unselect:
	usbhsf_fifo_unselect(pipe, fifo);
usbhsf_pio_prepare_pop:

	/*
	 * change handler to PIO
	 */
	pkt->handler = &usbhs_fifo_pio_pop_handler;
	usbhs_pipe_config_change_bfre(pipe, 0);

	return pkt->handler->prepare(pkt, is_done);
}