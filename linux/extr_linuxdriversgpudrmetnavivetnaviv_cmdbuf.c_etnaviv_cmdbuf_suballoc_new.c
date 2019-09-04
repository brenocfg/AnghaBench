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
struct etnaviv_gpu {int /*<<< orphan*/  dev; } ;
struct etnaviv_cmdbuf_suballoc {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  iova; int /*<<< orphan*/  vram_node; int /*<<< orphan*/  free_event; int /*<<< orphan*/  lock; struct etnaviv_gpu* gpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct etnaviv_cmdbuf_suballoc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SUBALLOC_SIZE ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int etnaviv_iommu_get_suballoc_va (struct etnaviv_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_cmdbuf_suballoc*) ; 
 struct etnaviv_cmdbuf_suballoc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct etnaviv_cmdbuf_suballoc *
etnaviv_cmdbuf_suballoc_new(struct etnaviv_gpu * gpu)
{
	struct etnaviv_cmdbuf_suballoc *suballoc;
	int ret;

	suballoc = kzalloc(sizeof(*suballoc), GFP_KERNEL);
	if (!suballoc)
		return ERR_PTR(-ENOMEM);

	suballoc->gpu = gpu;
	mutex_init(&suballoc->lock);
	init_waitqueue_head(&suballoc->free_event);

	suballoc->vaddr = dma_alloc_wc(gpu->dev, SUBALLOC_SIZE,
				       &suballoc->paddr, GFP_KERNEL);
	if (!suballoc->vaddr)
		goto free_suballoc;

	ret = etnaviv_iommu_get_suballoc_va(gpu, suballoc->paddr,
					    &suballoc->vram_node, SUBALLOC_SIZE,
					    &suballoc->iova);
	if (ret)
		goto free_dma;

	return suballoc;

free_dma:
	dma_free_wc(gpu->dev, SUBALLOC_SIZE, suballoc->vaddr, suballoc->paddr);
free_suballoc:
	kfree(suballoc);

	return NULL;
}