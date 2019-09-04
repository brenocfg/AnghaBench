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
struct sprd_dma_chn {int /*<<< orphan*/  dev_id; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_DMA_SOFTWARE_UID ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sprd_dma_alloc_chan_resources(struct dma_chan *chan)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	int ret;

	ret = pm_runtime_get_sync(chan->device->dev);
	if (ret < 0)
		return ret;

	schan->dev_id = SPRD_DMA_SOFTWARE_UID;
	return 0;
}