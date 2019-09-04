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
struct vpdma_buf {int mapped; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 

int vpdma_map_desc_buf(struct vpdma_data *vpdma, struct vpdma_buf *buf)
{
	struct device *dev = &vpdma->pdev->dev;

	WARN_ON(buf->mapped);
	buf->dma_addr = dma_map_single(dev, buf->addr, buf->size,
				DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, buf->dma_addr)) {
		dev_err(dev, "failed to map buffer\n");
		return -EINVAL;
	}

	buf->mapped = true;

	return 0;
}