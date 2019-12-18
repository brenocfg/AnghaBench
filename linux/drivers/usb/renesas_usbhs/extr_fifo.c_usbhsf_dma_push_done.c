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
struct usbhs_pkt {int trans; scalar_t__ actual; scalar_t__ length; TYPE_1__* handler; int /*<<< orphan*/  zero; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int /*<<< orphan*/  fifo; } ;
struct TYPE_2__ {int (* try_run ) (struct usbhs_pkt*,int*) ;} ;

/* Variables and functions */
 int stub1 (struct usbhs_pkt*,int*) ; 
 TYPE_1__ usbhs_fifo_pio_push_handler ; 
 int usbhs_pipe_get_maxpacket (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_running (struct usbhs_pipe*,int) ; 
 int /*<<< orphan*/  usbhsf_dma_stop (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_dma_unmap (struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsf_dma_push_done(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	int is_short = pkt->trans % usbhs_pipe_get_maxpacket(pipe);

	pkt->actual += pkt->trans;

	if (pkt->actual < pkt->length)
		*is_done = 0;		/* there are remainder data */
	else if (is_short)
		*is_done = 1;		/* short packet */
	else
		*is_done = !pkt->zero;	/* send zero packet? */

	usbhs_pipe_running(pipe, !*is_done);

	usbhsf_dma_stop(pipe, pipe->fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unselect(pipe, pipe->fifo);

	if (!*is_done) {
		/* change handler to PIO */
		pkt->handler = &usbhs_fifo_pio_push_handler;
		return pkt->handler->try_run(pkt, is_done);
	}

	return 0;
}