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
struct xgene_dma {TYPE_1__* chan; int /*<<< orphan*/ * dma_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int XGENE_DMA_MAX_CHANNEL ; 
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int xgene_dma_async_register (struct xgene_dma*,int) ; 

__attribute__((used)) static int xgene_dma_init_async(struct xgene_dma *pdma)
{
	int ret, i, j;

	for (i = 0; i < XGENE_DMA_MAX_CHANNEL ; i++) {
		ret = xgene_dma_async_register(pdma, i);
		if (ret) {
			for (j = 0; j < i; j++) {
				dma_async_device_unregister(&pdma->dma_dev[j]);
				tasklet_kill(&pdma->chan[j].tasklet);
			}

			return ret;
		}
	}

	return ret;
}