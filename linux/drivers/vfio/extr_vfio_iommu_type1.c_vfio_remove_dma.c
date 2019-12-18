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
struct vfio_iommu {int /*<<< orphan*/  dma_avail; } ;
struct vfio_dma {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vfio_dma*) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_unlink_dma (struct vfio_iommu*,struct vfio_dma*) ; 
 int /*<<< orphan*/  vfio_unmap_unpin (struct vfio_iommu*,struct vfio_dma*,int) ; 

__attribute__((used)) static void vfio_remove_dma(struct vfio_iommu *iommu, struct vfio_dma *dma)
{
	vfio_unmap_unpin(iommu, dma, true);
	vfio_unlink_dma(iommu, dma);
	put_task_struct(dma->task);
	kfree(dma);
	iommu->dma_avail++;
}