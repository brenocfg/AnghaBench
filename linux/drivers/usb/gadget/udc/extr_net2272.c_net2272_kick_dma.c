#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int length; unsigned int actual; scalar_t__ dma; } ;
struct net2272_request {TYPE_2__ req; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct net2272_ep {int num; int not_empty; TYPE_3__* dev; scalar_t__ is_in; TYPE_1__ ep; int /*<<< orphan*/  dma; } ;
struct TYPE_8__ {int dma_eot_polarity; int dma_dack_polarity; int dma_dreq_polarity; scalar_t__ dma_busy; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALT_NAK_OUT_PACKETS ; 
 int BUFFER_EMPTY ; 
 int DACK_POLARITY ; 
 int /*<<< orphan*/  DMAREQ ; 
 int DMA_BUFFER_VALID ; 
 int DMA_CONTROL_DACK ; 
 int DMA_ENDPOINT_SELECT ; 
 int DMA_REQUEST_ENABLE ; 
 int DREQ_POLARITY ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOT_POLARITY ; 
 int /*<<< orphan*/  EP_IRQENB ; 
 int /*<<< orphan*/  EP_RSPCLR ; 
 int /*<<< orphan*/  EP_RSPSET ; 
 int /*<<< orphan*/  EP_STAT0 ; 
 int SHORT_PACKET_TRANSFERRED_INTERRUPT ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct net2272_request*,unsigned long long) ; 
 int net2272_ep_read (struct net2272_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net2272_ep_write (struct net2272_ep*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net2272_request_dma (TYPE_3__*,int,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  net2272_start_dma (TYPE_3__*) ; 
 int /*<<< orphan*/  net2272_write (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  use_dma ; 

__attribute__((used)) static int
net2272_kick_dma(struct net2272_ep *ep, struct net2272_request *req)
{
	unsigned size;
	u8 tmp;

	if (!use_dma || (ep->num < 1) || (ep->num > 2) || !ep->dma)
		return -EINVAL;

	/* don't use dma for odd-length transfers
	 * otherwise, we'd need to deal with the last byte with pio
	 */
	if (req->req.length & 1)
		return -EINVAL;

	dev_vdbg(ep->dev->dev, "kick_dma %s req %p dma %08llx\n",
		ep->ep.name, req, (unsigned long long) req->req.dma);

	net2272_ep_write(ep, EP_RSPSET, 1 << ALT_NAK_OUT_PACKETS);

	/* The NET2272 can only use DMA on one endpoint at a time */
	if (ep->dev->dma_busy)
		return -EBUSY;

	/* Make sure we only DMA an even number of bytes (we'll use
	 * pio to complete the transfer)
	 */
	size = req->req.length;
	size &= ~1;

	/* device-to-host transfer */
	if (ep->is_in) {
		/* initialize platform's dma controller */
		if (net2272_request_dma(ep->dev, ep->num, req->req.dma, size, 0))
			/* unable to obtain DMA channel; return error and use pio mode */
			return -EBUSY;
		req->req.actual += size;

	/* host-to-device transfer */
	} else {
		tmp = net2272_ep_read(ep, EP_STAT0);

		/* initialize platform's dma controller */
		if (net2272_request_dma(ep->dev, ep->num, req->req.dma, size, 1))
			/* unable to obtain DMA channel; return error and use pio mode */
			return -EBUSY;

		if (!(tmp & (1 << BUFFER_EMPTY)))
			ep->not_empty = 1;
		else
			ep->not_empty = 0;


		/* allow the endpoint's buffer to fill */
		net2272_ep_write(ep, EP_RSPCLR, 1 << ALT_NAK_OUT_PACKETS);

		/* this transfer completed and data's already in the fifo
		 * return error so pio gets used.
		 */
		if (tmp & (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT)) {

			/* deassert dreq */
			net2272_write(ep->dev, DMAREQ,
				(0 << DMA_BUFFER_VALID) |
				(0 << DMA_REQUEST_ENABLE) |
				(1 << DMA_CONTROL_DACK) |
				(ep->dev->dma_eot_polarity << EOT_POLARITY) |
				(ep->dev->dma_dack_polarity << DACK_POLARITY) |
				(ep->dev->dma_dreq_polarity << DREQ_POLARITY) |
				((ep->num >> 1) << DMA_ENDPOINT_SELECT));

			return -EBUSY;
		}
	}

	/* Don't use per-packet interrupts: use dma interrupts only */
	net2272_ep_write(ep, EP_IRQENB, 0);

	net2272_start_dma(ep->dev);

	return 0;
}