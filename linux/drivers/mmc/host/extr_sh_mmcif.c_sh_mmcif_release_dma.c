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
struct sh_mmcif_host {int dma_active; struct dma_chan* chan_rx; struct dma_chan* chan_tx; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int BUF_ACC_DMAREN ; 
 int BUF_ACC_DMAWEN ; 
 int /*<<< orphan*/  MMCIF_CE_BUF_ACC ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 int /*<<< orphan*/  sh_mmcif_bitclr (struct sh_mmcif_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_mmcif_release_dma(struct sh_mmcif_host *host)
{
	sh_mmcif_bitclr(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAREN | BUF_ACC_DMAWEN);
	/* Descriptors are freed automatically */
	if (host->chan_tx) {
		struct dma_chan *chan = host->chan_tx;
		host->chan_tx = NULL;
		dma_release_channel(chan);
	}
	if (host->chan_rx) {
		struct dma_chan *chan = host->chan_rx;
		host->chan_rx = NULL;
		dma_release_channel(chan);
	}

	host->dma_active = false;
}