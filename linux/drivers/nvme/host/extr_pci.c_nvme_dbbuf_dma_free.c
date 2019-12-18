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
struct nvme_dev {int /*<<< orphan*/ * dbbuf_eis; int /*<<< orphan*/  dbbuf_eis_dma_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/ * dbbuf_dbs; int /*<<< orphan*/  dbbuf_dbs_dma_addr; int /*<<< orphan*/  db_stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int nvme_dbbuf_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_dbbuf_dma_free(struct nvme_dev *dev)
{
	unsigned int mem_size = nvme_dbbuf_size(dev->db_stride);

	if (dev->dbbuf_dbs) {
		dma_free_coherent(dev->dev, mem_size,
				  dev->dbbuf_dbs, dev->dbbuf_dbs_dma_addr);
		dev->dbbuf_dbs = NULL;
	}
	if (dev->dbbuf_eis) {
		dma_free_coherent(dev->dev, mem_size,
				  dev->dbbuf_eis, dev->dbbuf_eis_dma_addr);
		dev->dbbuf_eis = NULL;
	}
}