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
struct etnaviv_cmdbuf_suballoc {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; TYPE_1__* gpu; int /*<<< orphan*/  iova; int /*<<< orphan*/  vram_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUBALLOC_SIZE ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_iommu_put_suballoc_va (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_cmdbuf_suballoc*) ; 

void etnaviv_cmdbuf_suballoc_destroy(struct etnaviv_cmdbuf_suballoc *suballoc)
{
	etnaviv_iommu_put_suballoc_va(suballoc->gpu, &suballoc->vram_node,
				      SUBALLOC_SIZE, suballoc->iova);
	dma_free_wc(suballoc->gpu->dev, SUBALLOC_SIZE, suballoc->vaddr,
		    suballoc->paddr);
	kfree(suballoc);
}