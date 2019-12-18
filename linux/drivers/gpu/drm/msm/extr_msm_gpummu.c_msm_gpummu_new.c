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
struct msm_mmu {int dummy; } ;
struct msm_gpummu {struct msm_mmu base; struct msm_gpu* gpu; int /*<<< orphan*/  table; int /*<<< orphan*/  pt_base; } ;
struct msm_gpu {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_FORCE_CONTIGUOUS ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct msm_mmu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 scalar_t__ TABLE_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dma_alloc_attrs (struct device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funcs ; 
 int /*<<< orphan*/  kfree (struct msm_gpummu*) ; 
 struct msm_gpummu* kzalloc (int,int) ; 
 int /*<<< orphan*/  msm_mmu_init (struct msm_mmu*,struct device*,int /*<<< orphan*/ *) ; 

struct msm_mmu *msm_gpummu_new(struct device *dev, struct msm_gpu *gpu)
{
	struct msm_gpummu *gpummu;

	gpummu = kzalloc(sizeof(*gpummu), GFP_KERNEL);
	if (!gpummu)
		return ERR_PTR(-ENOMEM);

	gpummu->table = dma_alloc_attrs(dev, TABLE_SIZE + 32, &gpummu->pt_base,
		GFP_KERNEL | __GFP_ZERO, DMA_ATTR_FORCE_CONTIGUOUS);
	if (!gpummu->table) {
		kfree(gpummu);
		return ERR_PTR(-ENOMEM);
	}

	gpummu->gpu = gpu;
	msm_mmu_init(&gpummu->base, dev, &funcs);

	return &gpummu->base;
}