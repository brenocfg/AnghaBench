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
struct ddb_input {int nr; TYPE_2__* redo; struct ddb_dma* dma; TYPE_1__* port; } ;
struct ddb_dvb {int /*<<< orphan*/  demux; } ;
struct ddb_dma {int cbuf; int stat; int ctrl; int size; int num; int /*<<< orphan*/ * vbuf; int /*<<< orphan*/ * pbuf; } ;
struct ddb {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct ddb_dma* dma; } ;
struct TYPE_3__ {struct ddb* dev; struct ddb_dvb* dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_ACK (struct ddb_dma*) ; 
 int /*<<< orphan*/  DMA_BUFFER_CONTROL (struct ddb_dma*) ; 
 int /*<<< orphan*/  DMA_BUFFER_CURRENT (struct ddb_dma*) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ alt_dma ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* safe_ddbreadl (struct ddb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_write_dvb(struct ddb_input *input,
			    struct ddb_input *input2)
{
	struct ddb_dvb *dvb = &input2->port->dvb[input2->nr & 1];
	struct ddb_dma *dma, *dma2;
	struct ddb *dev = input->port->dev;
	int ack = 1;

	dma = input->dma;
	dma2 = input->dma;
	/*
	 * if there also is an output connected, do not ACK.
	 * input_write_output will ACK.
	 */
	if (input->redo) {
		dma2 = input->redo->dma;
		ack = 0;
	}
	while (dma->cbuf != ((dma->stat >> 11) & 0x1f) ||
	       (4 & dma->ctrl)) {
		if (4 & dma->ctrl) {
			/* dev_err(dev->dev, "Overflow dma %d\n", dma->nr); */
			ack = 1;
		}
		if (alt_dma)
			dma_sync_single_for_cpu(dev->dev, dma2->pbuf[dma->cbuf],
						dma2->size, DMA_FROM_DEVICE);
		dvb_dmx_swfilter_packets(&dvb->demux,
					 dma2->vbuf[dma->cbuf],
					 dma2->size / 188);
		dma->cbuf = (dma->cbuf + 1) % dma2->num;
		if (ack)
			ddbwritel(dev, (dma->cbuf << 11),
				  DMA_BUFFER_ACK(dma));
		dma->stat = safe_ddbreadl(dev, DMA_BUFFER_CURRENT(dma));
		dma->ctrl = safe_ddbreadl(dev, DMA_BUFFER_CONTROL(dma));
	}
}