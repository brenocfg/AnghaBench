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
struct mic_device {scalar_t__ num_dma_ch; TYPE_2__* pdev; struct dma_chan** dma_ch; TYPE_1__* ops; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 scalar_t__ MIC_MAX_DMA_CHAN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mic_request_dma_chans(struct mic_device *mdev)
{
	dma_cap_mask_t mask;
	struct dma_chan *chan;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	do {
		chan = dma_request_channel(mask, mdev->ops->dma_filter,
					   &mdev->pdev->dev);
		if (chan) {
			mdev->dma_ch[mdev->num_dma_ch++] = chan;
			if (mdev->num_dma_ch >= MIC_MAX_DMA_CHAN)
				break;
		}
	} while (chan);
	dev_info(&mdev->pdev->dev, "DMA channels # %d\n", mdev->num_dma_ch);
	return mdev->num_dma_ch;
}