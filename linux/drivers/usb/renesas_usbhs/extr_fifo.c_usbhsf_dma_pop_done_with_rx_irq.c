#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usbhs_pkt {scalar_t__ actual; int trans; scalar_t__ length; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int usbhs_pipe_get_maxpacket (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_running (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_dma_stop (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_dma_unmap (struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_fifo_unselect (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsf_prepare_pop (struct usbhs_pkt*,int*) ; 

__attribute__((used)) static int usbhsf_dma_pop_done_with_rx_irq(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	int maxp = usbhs_pipe_get_maxpacket(pipe);

	usbhsf_dma_stop(pipe, pipe->fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unselect(pipe, pipe->fifo);

	pkt->actual += pkt->trans;

	if ((pkt->actual == pkt->length) ||	/* receive all data */
	    (pkt->trans < maxp)) {		/* short packet */
		*is_done = 1;
		usbhs_pipe_running(pipe, 0);
	} else {
		/* re-enable */
		usbhs_pipe_running(pipe, 0);
		usbhsf_prepare_pop(pkt, is_done);
	}

	return 0;
}