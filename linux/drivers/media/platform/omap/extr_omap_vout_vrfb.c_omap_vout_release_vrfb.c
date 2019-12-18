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
struct TYPE_2__ {scalar_t__ req_status; int /*<<< orphan*/  chan; int /*<<< orphan*/  xt; } ;
struct omap_vout_device {TYPE_1__ vrfb_dma_tx; int /*<<< orphan*/ * vrfb_context; } ;

/* Variables and functions */
 scalar_t__ DMA_CHAN_ALLOTED ; 
 scalar_t__ DMA_CHAN_NOT_ALLOTED ; 
 int VRFB_NUM_BUFS ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_vrfb_release_ctx (int /*<<< orphan*/ *) ; 

void omap_vout_release_vrfb(struct omap_vout_device *vout)
{
	int i;

	for (i = 0; i < VRFB_NUM_BUFS; i++)
		omap_vrfb_release_ctx(&vout->vrfb_context[i]);

	if (vout->vrfb_dma_tx.req_status == DMA_CHAN_ALLOTED) {
		vout->vrfb_dma_tx.req_status = DMA_CHAN_NOT_ALLOTED;
		kfree(vout->vrfb_dma_tx.xt);
		dmaengine_terminate_sync(vout->vrfb_dma_tx.chan);
		dma_release_channel(vout->vrfb_dma_tx.chan);
	}
}