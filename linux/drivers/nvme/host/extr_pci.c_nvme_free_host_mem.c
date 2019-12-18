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
struct nvme_host_mem_buf_desc {int /*<<< orphan*/  addr; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {size_t page_size; } ;
struct nvme_dev {int nr_host_mem_descs; struct nvme_host_mem_buf_desc* host_mem_descs; int /*<<< orphan*/  host_mem_descs_dma; int /*<<< orphan*/  dev; int /*<<< orphan*/ * host_mem_desc_bufs; TYPE_1__ ctrl; } ;

/* Variables and functions */
 int DMA_ATTR_NO_KERNEL_MAPPING ; 
 int DMA_ATTR_NO_WARN ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct nvme_host_mem_buf_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_free_host_mem(struct nvme_dev *dev)
{
	int i;

	for (i = 0; i < dev->nr_host_mem_descs; i++) {
		struct nvme_host_mem_buf_desc *desc = &dev->host_mem_descs[i];
		size_t size = le32_to_cpu(desc->size) * dev->ctrl.page_size;

		dma_free_attrs(dev->dev, size, dev->host_mem_desc_bufs[i],
			       le64_to_cpu(desc->addr),
			       DMA_ATTR_NO_KERNEL_MAPPING | DMA_ATTR_NO_WARN);
	}

	kfree(dev->host_mem_desc_bufs);
	dev->host_mem_desc_bufs = NULL;
	dma_free_coherent(dev->dev,
			dev->nr_host_mem_descs * sizeof(*dev->host_mem_descs),
			dev->host_mem_descs, dev->host_mem_descs_dma);
	dev->host_mem_descs = NULL;
	dev->nr_host_mem_descs = 0;
}