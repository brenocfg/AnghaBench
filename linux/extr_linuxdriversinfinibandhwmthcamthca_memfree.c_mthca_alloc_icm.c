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
struct mthca_icm_chunk {size_t npages; scalar_t__ nsg; int /*<<< orphan*/ * mem; int /*<<< orphan*/  list; } ;
struct mthca_icm {int /*<<< orphan*/  chunk_list; scalar_t__ refcount; } ;
struct mthca_dev {TYPE_1__* pdev; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTHCA_ICM_ALLOC_SIZE ; 
 size_t MTHCA_ICM_CHUNK_LEN ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NOWARN ; 
 int get_order (int /*<<< orphan*/ ) ; 
 void* kmalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mthca_alloc_icm_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int mthca_alloc_icm_pages (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mthca_free_icm (struct mthca_dev*,struct mthca_icm*,int) ; 
 void* pci_map_sg (TYPE_1__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,size_t) ; 

struct mthca_icm *mthca_alloc_icm(struct mthca_dev *dev, int npages,
				  gfp_t gfp_mask, int coherent)
{
	struct mthca_icm *icm;
	struct mthca_icm_chunk *chunk = NULL;
	int cur_order;
	int ret;

	/* We use sg_set_buf for coherent allocs, which assumes low memory */
	BUG_ON(coherent && (gfp_mask & __GFP_HIGHMEM));

	icm = kmalloc(sizeof *icm, gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
	if (!icm)
		return icm;

	icm->refcount = 0;
	INIT_LIST_HEAD(&icm->chunk_list);

	cur_order = get_order(MTHCA_ICM_ALLOC_SIZE);

	while (npages > 0) {
		if (!chunk) {
			chunk = kmalloc(sizeof *chunk,
					gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
			if (!chunk)
				goto fail;

			sg_init_table(chunk->mem, MTHCA_ICM_CHUNK_LEN);
			chunk->npages = 0;
			chunk->nsg    = 0;
			list_add_tail(&chunk->list, &icm->chunk_list);
		}

		while (1 << cur_order > npages)
			--cur_order;

		if (coherent)
			ret = mthca_alloc_icm_coherent(&dev->pdev->dev,
						       &chunk->mem[chunk->npages],
						       cur_order, gfp_mask);
		else
			ret = mthca_alloc_icm_pages(&chunk->mem[chunk->npages],
						    cur_order, gfp_mask);

		if (!ret) {
			++chunk->npages;

			if (coherent)
				++chunk->nsg;
			else if (chunk->npages == MTHCA_ICM_CHUNK_LEN) {
				chunk->nsg = pci_map_sg(dev->pdev, chunk->mem,
							chunk->npages,
							PCI_DMA_BIDIRECTIONAL);

				if (chunk->nsg <= 0)
					goto fail;
			}

			if (chunk->npages == MTHCA_ICM_CHUNK_LEN)
				chunk = NULL;

			npages -= 1 << cur_order;
		} else {
			--cur_order;
			if (cur_order < 0)
				goto fail;
		}
	}

	if (!coherent && chunk) {
		chunk->nsg = pci_map_sg(dev->pdev, chunk->mem,
					chunk->npages,
					PCI_DMA_BIDIRECTIONAL);

		if (chunk->nsg <= 0)
			goto fail;
	}

	return icm;

fail:
	mthca_free_icm(dev, icm, coherent);
	return NULL;
}