#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_vde {int /*<<< orphan*/  iova; TYPE_2__* domain; } ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct iova {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {unsigned long aperture_end; } ;
struct TYPE_4__ {TYPE_1__ geometry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int /*<<< orphan*/  __free_iova (int /*<<< orphan*/ *,struct iova*) ; 
 struct iova* alloc_iova (int /*<<< orphan*/ *,size_t,unsigned long,int) ; 
 size_t iommu_map_sg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t iova_align (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  iova_dma_addr (int /*<<< orphan*/ *,struct iova*) ; 
 unsigned long iova_shift (int /*<<< orphan*/ *) ; 

int tegra_vde_iommu_map(struct tegra_vde *vde,
			struct sg_table *sgt,
			struct iova **iovap,
			size_t size)
{
	struct iova *iova;
	unsigned long shift;
	unsigned long end;
	dma_addr_t addr;

	end = vde->domain->geometry.aperture_end;
	size = iova_align(&vde->iova, size);
	shift = iova_shift(&vde->iova);

	iova = alloc_iova(&vde->iova, size >> shift, end >> shift, true);
	if (!iova)
		return -ENOMEM;

	addr = iova_dma_addr(&vde->iova, iova);

	size = iommu_map_sg(vde->domain, addr, sgt->sgl, sgt->nents,
			    IOMMU_READ | IOMMU_WRITE);
	if (!size) {
		__free_iova(&vde->iova, iova);
		return -ENXIO;
	}

	*iovap = iova;

	return 0;
}