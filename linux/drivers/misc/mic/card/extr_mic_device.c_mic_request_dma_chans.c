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
struct mic_driver {scalar_t__ num_dma_ch; int /*<<< orphan*/  dev; struct dma_chan** dma_ch; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 scalar_t__ MIC_MAX_DMA_CHAN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mic_request_dma_chans(struct mic_driver *mdrv)
{
	dma_cap_mask_t mask;
	struct dma_chan *chan;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	do {
		chan = dma_request_channel(mask, NULL, NULL);
		if (chan) {
			mdrv->dma_ch[mdrv->num_dma_ch++] = chan;
			if (mdrv->num_dma_ch >= MIC_MAX_DMA_CHAN)
				break;
		}
	} while (chan);
	dev_info(mdrv->dev, "DMA channels # %d\n", mdrv->num_dma_ch);
	return mdrv->num_dma_ch;
}