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
struct ntb_transport_qp {int tx_max_frame; struct dma_chan* tx_dma_chan; struct dma_chan* rx_dma_chan; } ;
struct ntb_payload_header {int dummy; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  copy_align; } ;

/* Variables and functions */
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int round_down (unsigned int,int) ; 

unsigned int ntb_transport_max_size(struct ntb_transport_qp *qp)
{
	unsigned int max_size;
	unsigned int copy_align;
	struct dma_chan *rx_chan, *tx_chan;

	if (!qp)
		return 0;

	rx_chan = qp->rx_dma_chan;
	tx_chan = qp->tx_dma_chan;

	copy_align = max(rx_chan ? rx_chan->device->copy_align : 0,
			 tx_chan ? tx_chan->device->copy_align : 0);

	/* If DMA engine usage is possible, try to find the max size for that */
	max_size = qp->tx_max_frame - sizeof(struct ntb_payload_header);
	max_size = round_down(max_size, 1 << copy_align);

	return max_size;
}