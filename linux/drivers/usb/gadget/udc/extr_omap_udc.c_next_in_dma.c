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
typedef  int u16 ;
struct TYPE_4__ {unsigned int length; unsigned int actual; scalar_t__ dma; } ;
struct omap_req {unsigned int dma_bytes; TYPE_2__ req; } ;
struct TYPE_3__ {int maxpacket; } ;
struct omap_ep {unsigned int maxpacket; int /*<<< orphan*/  dma_channel; int /*<<< orphan*/  lch; int /*<<< orphan*/  dma_counter; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DMA_AMODE_POST_INC ; 
 int /*<<< orphan*/  OMAP_DMA_DATA_TYPE_S16 ; 
 int /*<<< orphan*/  OMAP_DMA_DATA_TYPE_S8 ; 
 int /*<<< orphan*/  OMAP_DMA_PORT_EMIFF ; 
 int OMAP_DMA_SYNC_ELEMENT ; 
 int OMAP_DMA_SYNC_FRAME ; 
 int /*<<< orphan*/  UDC_DMA_IRQ_EN ; 
 int /*<<< orphan*/  UDC_TXDMA (int /*<<< orphan*/ ) ; 
 unsigned int UDC_TXN_EOT ; 
 int UDC_TXN_START ; 
 unsigned int UDC_TXN_TSC ; 
 int UDC_TX_DONE_IE (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_omap15xx () ; 
 scalar_t__ cpu_is_omap16xx () ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  omap_get_dma_src_pos (int /*<<< orphan*/ ) ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_src_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_dma_transfer_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_start_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void next_in_dma(struct omap_ep *ep, struct omap_req *req)
{
	u16		txdma_ctrl, w;
	unsigned	length = req->req.length - req->req.actual;
	const int	sync_mode = cpu_is_omap15xx()
				? OMAP_DMA_SYNC_FRAME
				: OMAP_DMA_SYNC_ELEMENT;
	int		dma_trigger = 0;

	/* measure length in either bytes or packets */
	if ((cpu_is_omap16xx() && length <= UDC_TXN_TSC)
			|| (cpu_is_omap15xx() && length < ep->maxpacket)) {
		txdma_ctrl = UDC_TXN_EOT | length;
		omap_set_dma_transfer_params(ep->lch, OMAP_DMA_DATA_TYPE_S8,
				length, 1, sync_mode, dma_trigger, 0);
	} else {
		length = min(length / ep->maxpacket,
				(unsigned) UDC_TXN_TSC + 1);
		txdma_ctrl = length;
		omap_set_dma_transfer_params(ep->lch, OMAP_DMA_DATA_TYPE_S16,
				ep->ep.maxpacket >> 1, length, sync_mode,
				dma_trigger, 0);
		length *= ep->maxpacket;
	}
	omap_set_dma_src_params(ep->lch, OMAP_DMA_PORT_EMIFF,
		OMAP_DMA_AMODE_POST_INC, req->req.dma + req->req.actual,
		0, 0);

	omap_start_dma(ep->lch);
	ep->dma_counter = omap_get_dma_src_pos(ep->lch);
	w = omap_readw(UDC_DMA_IRQ_EN);
	w |= UDC_TX_DONE_IE(ep->dma_channel);
	omap_writew(w, UDC_DMA_IRQ_EN);
	omap_writew(UDC_TXN_START | txdma_ctrl, UDC_TXDMA(ep->dma_channel));
	req->dma_bytes = length;
}