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
struct vio_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (void*) ; 

__attribute__((used)) static void free_dma_buffer(struct vio_dev *vdev, size_t size, void *vaddr,
			    dma_addr_t dma_handle)
{
	/* DMA unmap */
	dma_unmap_single(&vdev->dev, dma_handle, size, DMA_BIDIRECTIONAL);

	/* deallocate memory */
	kzfree(vaddr);
}