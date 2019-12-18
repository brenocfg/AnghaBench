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
struct usbhs_pkt {size_t length; int /*<<< orphan*/  cookie; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct dma_tx_state {size_t residue; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ USBHS_USB_DMAC_XFER_SIZE ; 
 int /*<<< orphan*/  dmaengine_tx_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int usbhs_pipe_get_maxpacket (struct usbhs_pipe*) ; 

__attribute__((used)) static size_t usbhs_dma_calc_received_size(struct usbhs_pkt *pkt,
					   struct dma_chan *chan, int dtln)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct dma_tx_state state;
	size_t received_size;
	int maxp = usbhs_pipe_get_maxpacket(pipe);

	dmaengine_tx_status(chan, pkt->cookie, &state);
	received_size = pkt->length - state.residue;

	if (dtln) {
		received_size -= USBHS_USB_DMAC_XFER_SIZE;
		received_size &= ~(maxp - 1);
		received_size += dtln;
	}

	return received_size;
}