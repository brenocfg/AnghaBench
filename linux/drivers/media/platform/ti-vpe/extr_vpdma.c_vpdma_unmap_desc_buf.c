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
struct vpdma_data {TYPE_1__* pdev; } ;
struct vpdma_buf {int mapped; int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vpdma_unmap_desc_buf(struct vpdma_data *vpdma, struct vpdma_buf *buf)
{
	struct device *dev = &vpdma->pdev->dev;

	if (buf->mapped)
		dma_unmap_single(dev, buf->dma_addr, buf->size,
				DMA_BIDIRECTIONAL);

	buf->mapped = false;
}