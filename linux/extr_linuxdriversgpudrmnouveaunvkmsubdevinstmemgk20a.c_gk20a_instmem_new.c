#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_instmem {int /*<<< orphan*/  subdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgshift; scalar_t__ domain; int /*<<< orphan*/  mm; int /*<<< orphan*/  mutex; } ;
struct nvkm_device_tegra {TYPE_3__* func; TYPE_2__ iommu; } ;
struct nvkm_device {TYPE_1__* func; } ;
struct gk20a_instmem {int vaddr_max; int attrs; struct nvkm_instmem base; int /*<<< orphan*/  iommu_bit; int /*<<< orphan*/  iommu_pgshift; scalar_t__ domain; int /*<<< orphan*/ * mm; int /*<<< orphan*/ * mm_mutex; int /*<<< orphan*/  vaddr_lru; scalar_t__ vaddr_use; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  iommu_bit; } ;
struct TYPE_4__ {struct nvkm_device_tegra* (* tegra ) (struct nvkm_device*) ;} ;

/* Variables and functions */
 int DMA_ATTR_NON_CONSISTENT ; 
 int DMA_ATTR_WEAK_ORDERING ; 
 int DMA_ATTR_WRITE_COMBINE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gk20a_instmem ; 
 struct gk20a_instmem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvkm_instmem_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_instmem*) ; 
 struct nvkm_device_tegra* stub1 (struct nvkm_device*) ; 

int
gk20a_instmem_new(struct nvkm_device *device, int index,
		  struct nvkm_instmem **pimem)
{
	struct nvkm_device_tegra *tdev = device->func->tegra(device);
	struct gk20a_instmem *imem;

	if (!(imem = kzalloc(sizeof(*imem), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_instmem_ctor(&gk20a_instmem, device, index, &imem->base);
	mutex_init(&imem->lock);
	*pimem = &imem->base;

	/* do not allow more than 1MB of CPU-mapped instmem */
	imem->vaddr_use = 0;
	imem->vaddr_max = 0x100000;
	INIT_LIST_HEAD(&imem->vaddr_lru);

	if (tdev->iommu.domain) {
		imem->mm_mutex = &tdev->iommu.mutex;
		imem->mm = &tdev->iommu.mm;
		imem->domain = tdev->iommu.domain;
		imem->iommu_pgshift = tdev->iommu.pgshift;
		imem->iommu_bit = tdev->func->iommu_bit;

		nvkm_info(&imem->base.subdev, "using IOMMU\n");
	} else {
		imem->attrs = DMA_ATTR_NON_CONSISTENT |
			      DMA_ATTR_WEAK_ORDERING |
			      DMA_ATTR_WRITE_COMBINE;

		nvkm_info(&imem->base.subdev, "using DMA API\n");
	}

	return 0;
}