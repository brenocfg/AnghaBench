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
struct sh_mobile_i2c_data {scalar_t__ dma_direction; TYPE_2__* msg; int /*<<< orphan*/  sg; struct dma_chan* dma_tx; struct dma_chan* dma_rx; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_mobile_i2c_dma_unmap(struct sh_mobile_i2c_data *pd)
{
	struct dma_chan *chan = pd->dma_direction == DMA_FROM_DEVICE
				? pd->dma_rx : pd->dma_tx;

	dma_unmap_single(chan->device->dev, sg_dma_address(&pd->sg),
			 pd->msg->len, pd->dma_direction);

	pd->dma_direction = DMA_NONE;
}