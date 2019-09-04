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
struct mxs_i2c_dev {int /*<<< orphan*/ * sg_io; int /*<<< orphan*/  dev; scalar_t__ dma_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxs_i2c_dma_finish(struct mxs_i2c_dev *i2c)
{
	if (i2c->dma_read) {
		dma_unmap_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
		dma_unmap_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FROM_DEVICE);
	} else {
		dma_unmap_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
	}
}