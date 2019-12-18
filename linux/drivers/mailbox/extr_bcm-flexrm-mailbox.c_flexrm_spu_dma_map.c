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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct brcm_message {TYPE_1__ spu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flexrm_spu_dma_map(struct device *dev, struct brcm_message *msg)
{
	int rc;

	rc = dma_map_sg(dev, msg->spu.src, sg_nents(msg->spu.src),
			DMA_TO_DEVICE);
	if (rc < 0)
		return rc;

	rc = dma_map_sg(dev, msg->spu.dst, sg_nents(msg->spu.dst),
			DMA_FROM_DEVICE);
	if (rc < 0) {
		dma_unmap_sg(dev, msg->spu.src, sg_nents(msg->spu.src),
			     DMA_TO_DEVICE);
		return rc;
	}

	return 0;
}