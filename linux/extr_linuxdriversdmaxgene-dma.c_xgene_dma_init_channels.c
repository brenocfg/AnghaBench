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
struct xgene_dma_chan {int id; int /*<<< orphan*/  name; struct xgene_dma* pdma; int /*<<< orphan*/  dev; } ;
struct xgene_dma {int /*<<< orphan*/  dev; struct xgene_dma_chan* chan; int /*<<< orphan*/  ring_num; } ;

/* Variables and functions */
 int XGENE_DMA_MAX_CHANNEL ; 
 int /*<<< orphan*/  XGENE_DMA_RING_NUM ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static void xgene_dma_init_channels(struct xgene_dma *pdma)
{
	struct xgene_dma_chan *chan;
	int i;

	pdma->ring_num = XGENE_DMA_RING_NUM;

	for (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) {
		chan = &pdma->chan[i];
		chan->dev = pdma->dev;
		chan->pdma = pdma;
		chan->id = i;
		snprintf(chan->name, sizeof(chan->name), "dmachan%d", chan->id);
	}
}