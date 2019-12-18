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
struct tegra_vde {int /*<<< orphan*/  iova; int /*<<< orphan*/  domain; } ;
struct iova {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __free_iova (int /*<<< orphan*/ *,struct iova*) ; 
 int /*<<< orphan*/  iommu_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iova_dma_addr (int /*<<< orphan*/ *,struct iova*) ; 
 unsigned long iova_shift (int /*<<< orphan*/ *) ; 
 unsigned long iova_size (struct iova*) ; 

void tegra_vde_iommu_unmap(struct tegra_vde *vde, struct iova *iova)
{
	unsigned long shift = iova_shift(&vde->iova);
	unsigned long size = iova_size(iova) << shift;
	dma_addr_t addr = iova_dma_addr(&vde->iova, iova);

	iommu_unmap(vde->domain, addr, size);
	__free_iova(&vde->iova, iova);
}