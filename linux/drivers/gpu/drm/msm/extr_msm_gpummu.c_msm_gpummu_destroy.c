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
struct msm_mmu {int /*<<< orphan*/  dev; } ;
struct msm_gpummu {int /*<<< orphan*/  pt_base; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_FORCE_CONTIGUOUS ; 
 int /*<<< orphan*/  TABLE_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msm_gpummu*) ; 
 struct msm_gpummu* to_msm_gpummu (struct msm_mmu*) ; 

__attribute__((used)) static void msm_gpummu_destroy(struct msm_mmu *mmu)
{
	struct msm_gpummu *gpummu = to_msm_gpummu(mmu);

	dma_free_attrs(mmu->dev, TABLE_SIZE, gpummu->table, gpummu->pt_base,
		DMA_ATTR_FORCE_CONTIGUOUS);

	kfree(gpummu);
}