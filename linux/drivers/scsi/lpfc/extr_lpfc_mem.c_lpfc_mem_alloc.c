#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lpfc_nodelist {int dummy; } ;
struct lpfc_node_rrq {int dummy; } ;
struct lpfc_dma_pool {TYPE_2__* elements; scalar_t__ current_count; scalar_t__ max_count; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/ * lpfc_mbuf_pool; int /*<<< orphan*/ * mbox_mem_pool; int /*<<< orphan*/ * nlp_mem_pool; int /*<<< orphan*/ * rrq_pool; int /*<<< orphan*/ * lpfc_hrb_pool; int /*<<< orphan*/ * lpfc_drb_pool; int /*<<< orphan*/ * device_data_mem_pool; scalar_t__ cfg_EnableXLane; int /*<<< orphan*/ * lpfc_hbq_pool; TYPE_1__* pcidev; struct lpfc_dma_pool lpfc_mbuf_safety_pool; } ;
struct lpfc_dmabuf {int dummy; } ;
struct lpfc_device_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LPFC_BPL_SIZE ; 
 int /*<<< orphan*/  LPFC_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  LPFC_DEVICE_DATA_POOL_SIZE ; 
 int /*<<< orphan*/  LPFC_HDR_BUF_SIZE ; 
 int LPFC_MBUF_POOL_SIZE ; 
 int /*<<< orphan*/  LPFC_MEM_POOL_SIZE ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 void* mempool_create_kmalloc_pool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 

int
lpfc_mem_alloc(struct lpfc_hba *phba, int align)
{
	struct lpfc_dma_pool *pool = &phba->lpfc_mbuf_safety_pool;
	int i;


	phba->lpfc_mbuf_pool = dma_pool_create("lpfc_mbuf_pool", &phba->pcidev->dev,
							LPFC_BPL_SIZE,
							align, 0);
	if (!phba->lpfc_mbuf_pool)
		goto fail;

	pool->elements = kmalloc_array(LPFC_MBUF_POOL_SIZE,
				       sizeof(struct lpfc_dmabuf),
				       GFP_KERNEL);
	if (!pool->elements)
		goto fail_free_lpfc_mbuf_pool;

	pool->max_count = 0;
	pool->current_count = 0;
	for ( i = 0; i < LPFC_MBUF_POOL_SIZE; i++) {
		pool->elements[i].virt = dma_pool_alloc(phba->lpfc_mbuf_pool,
				       GFP_KERNEL, &pool->elements[i].phys);
		if (!pool->elements[i].virt)
			goto fail_free_mbuf_pool;
		pool->max_count++;
		pool->current_count++;
	}

	phba->mbox_mem_pool = mempool_create_kmalloc_pool(LPFC_MEM_POOL_SIZE,
							 sizeof(LPFC_MBOXQ_t));
	if (!phba->mbox_mem_pool)
		goto fail_free_mbuf_pool;

	phba->nlp_mem_pool = mempool_create_kmalloc_pool(LPFC_MEM_POOL_SIZE,
						sizeof(struct lpfc_nodelist));
	if (!phba->nlp_mem_pool)
		goto fail_free_mbox_pool;

	if (phba->sli_rev == LPFC_SLI_REV4) {
		phba->rrq_pool =
			mempool_create_kmalloc_pool(LPFC_MEM_POOL_SIZE,
						sizeof(struct lpfc_node_rrq));
		if (!phba->rrq_pool)
			goto fail_free_nlp_mem_pool;
		phba->lpfc_hrb_pool = dma_pool_create("lpfc_hrb_pool",
					      &phba->pcidev->dev,
					      LPFC_HDR_BUF_SIZE, align, 0);
		if (!phba->lpfc_hrb_pool)
			goto fail_free_rrq_mem_pool;

		phba->lpfc_drb_pool = dma_pool_create("lpfc_drb_pool",
					      &phba->pcidev->dev,
					      LPFC_DATA_BUF_SIZE, align, 0);
		if (!phba->lpfc_drb_pool)
			goto fail_free_hrb_pool;
		phba->lpfc_hbq_pool = NULL;
	} else {
		phba->lpfc_hbq_pool = dma_pool_create("lpfc_hbq_pool",
			&phba->pcidev->dev, LPFC_BPL_SIZE, align, 0);
		if (!phba->lpfc_hbq_pool)
			goto fail_free_nlp_mem_pool;
		phba->lpfc_hrb_pool = NULL;
		phba->lpfc_drb_pool = NULL;
	}

	if (phba->cfg_EnableXLane) {
		phba->device_data_mem_pool = mempool_create_kmalloc_pool(
					LPFC_DEVICE_DATA_POOL_SIZE,
					sizeof(struct lpfc_device_data));
		if (!phba->device_data_mem_pool)
			goto fail_free_drb_pool;
	} else {
		phba->device_data_mem_pool = NULL;
	}

	return 0;
fail_free_drb_pool:
	dma_pool_destroy(phba->lpfc_drb_pool);
	phba->lpfc_drb_pool = NULL;
 fail_free_hrb_pool:
	dma_pool_destroy(phba->lpfc_hrb_pool);
	phba->lpfc_hrb_pool = NULL;
 fail_free_rrq_mem_pool:
	mempool_destroy(phba->rrq_pool);
	phba->rrq_pool = NULL;
 fail_free_nlp_mem_pool:
	mempool_destroy(phba->nlp_mem_pool);
	phba->nlp_mem_pool = NULL;
 fail_free_mbox_pool:
	mempool_destroy(phba->mbox_mem_pool);
	phba->mbox_mem_pool = NULL;
 fail_free_mbuf_pool:
	while (i--)
		dma_pool_free(phba->lpfc_mbuf_pool, pool->elements[i].virt,
						 pool->elements[i].phys);
	kfree(pool->elements);
 fail_free_lpfc_mbuf_pool:
	dma_pool_destroy(phba->lpfc_mbuf_pool);
	phba->lpfc_mbuf_pool = NULL;
 fail:
	return -ENOMEM;
}