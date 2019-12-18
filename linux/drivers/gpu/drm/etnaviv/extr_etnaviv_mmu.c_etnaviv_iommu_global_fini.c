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
struct TYPE_3__ {int /*<<< orphan*/  pta_dma; scalar_t__ pta_cpu; } ;
struct etnaviv_iommu_global {scalar_t__ use; int /*<<< orphan*/  lock; int /*<<< orphan*/  bad_page_dma; scalar_t__ bad_page_cpu; int /*<<< orphan*/  dev; TYPE_1__ v2; } ;
struct etnaviv_gpu {TYPE_2__* drm; } ;
struct etnaviv_drm_private {struct etnaviv_iommu_global* mmu_global; } ;
struct TYPE_4__ {struct etnaviv_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETNAVIV_PTA_SIZE ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommu_global*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void etnaviv_iommu_global_fini(struct etnaviv_gpu *gpu)
{
	struct etnaviv_drm_private *priv = gpu->drm->dev_private;
	struct etnaviv_iommu_global *global = priv->mmu_global;

	if (--global->use > 0)
		return;

	if (global->v2.pta_cpu)
		dma_free_wc(global->dev, ETNAVIV_PTA_SIZE,
			    global->v2.pta_cpu, global->v2.pta_dma);

	if (global->bad_page_cpu)
		dma_free_wc(global->dev, SZ_4K,
			    global->bad_page_cpu, global->bad_page_dma);

	mutex_destroy(&global->lock);
	kfree(global);

	priv->mmu_global = NULL;
}