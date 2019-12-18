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
struct efa_dev {int /*<<< orphan*/  ibdev; TYPE_1__* pdev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 void* alloc_pages_exact (size_t,int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,void*,size_t,int) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages_exact (void*,size_t) ; 
 int /*<<< orphan*/  ibdev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void *efa_zalloc_mapped(struct efa_dev *dev, dma_addr_t *dma_addr,
			       size_t size, enum dma_data_direction dir)
{
	void *addr;

	addr = alloc_pages_exact(size, GFP_KERNEL | __GFP_ZERO);
	if (!addr)
		return NULL;

	*dma_addr = dma_map_single(&dev->pdev->dev, addr, size, dir);
	if (dma_mapping_error(&dev->pdev->dev, *dma_addr)) {
		ibdev_err(&dev->ibdev, "Failed to map DMA address\n");
		free_pages_exact(addr, size);
		return NULL;
	}

	return addr;
}