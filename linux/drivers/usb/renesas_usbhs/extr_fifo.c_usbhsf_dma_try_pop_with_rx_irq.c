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
struct usbhs_pkt {int trans; TYPE_1__* handler; int /*<<< orphan*/  work; scalar_t__ actual; scalar_t__ length; scalar_t__ buf; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int dummy; } ;
struct TYPE_2__ {int (* try_run ) (struct usbhs_pkt*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  pio_dma_border ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int stub1 (struct usbhs_pkt*,int*) ; 
 TYPE_1__ usbhs_fifo_pio_pop_handler ; 
 int usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbhs_pipe_is_busy (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 scalar_t__ usbhsf_dma_map (struct usbhs_pkt*) ; 
 int usbhsf_fifo_barrier (struct usbhs_priv*,struct usbhs_fifo*) ; 
 int usbhsf_fifo_rcv_len (struct usbhs_priv*,struct usbhs_fifo*) ; 
 int usbhsf_fifo_select (struct usbhs_pipe*,struct usbhs_fifo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 struct usbhs_fifo* usbhsf_get_dma_fifo (struct usbhs_priv*,struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_rx_irq_ctrl (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfer_work ; 

__attribute__((used)) static int usbhsf_dma_try_pop_with_rx_irq(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_fifo *fifo;
	int len, ret;

	if (usbhs_pipe_is_busy(pipe))
		return 0;

	if (usbhs_pipe_is_dcp(pipe))
		goto usbhsf_pio_prepare_pop;

	/* get enable DMA fifo */
	fifo = usbhsf_get_dma_fifo(priv, pkt);
	if (!fifo)
		goto usbhsf_pio_prepare_pop;

	if ((uintptr_t)(pkt->buf + pkt->actual) & 0x7) /* 8byte alignment */
		goto usbhsf_pio_prepare_pop;

	ret = usbhsf_fifo_select(pipe, fifo, 0);
	if (ret < 0)
		goto usbhsf_pio_prepare_pop;

	/* use PIO if packet is less than pio_dma_border */
	len = usbhsf_fifo_rcv_len(priv, fifo);
	len = min(pkt->length - pkt->actual, len);
	if (len & 0x7) /* 8byte alignment */
		goto usbhsf_pio_prepare_pop_unselect;

	if (len < usbhs_get_dparam(priv, pio_dma_border))
		goto usbhsf_pio_prepare_pop_unselect;

	ret = usbhsf_fifo_barrier(priv, fifo);
	if (ret < 0)
		goto usbhsf_pio_prepare_pop_unselect;

	if (usbhsf_dma_map(pkt) < 0)
		goto usbhsf_pio_prepare_pop_unselect;

	/* DMA */

	/*
	 * usbhs_fifo_dma_pop_handler :: prepare
	 * enabled irq to come here.
	 * but it is no longer needed for DMA. disable it.
	 */
	usbhsf_rx_irq_ctrl(pipe, 0);

	pkt->trans = len;

	INIT_WORK(&pkt->work, xfer_work);
	schedule_work(&pkt->work);

	return 0;

usbhsf_pio_prepare_pop_unselect:
	usbhsf_fifo_unselect(pipe, fifo);
usbhsf_pio_prepare_pop:

	/*
	 * change handler to PIO
	 */
	pkt->handler = &usbhs_fifo_pio_pop_handler;

	return pkt->handler->try_run(pkt, is_done);
}