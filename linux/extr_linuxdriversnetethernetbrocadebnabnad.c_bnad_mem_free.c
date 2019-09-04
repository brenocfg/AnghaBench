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
struct bnad {TYPE_1__* pcidev; } ;
struct bna_mem_info {int num; scalar_t__ mem_type; TYPE_2__* mdl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {struct TYPE_5__* kva; int /*<<< orphan*/  len; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_GET_DMA_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BNA_MEM_T_DMA ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void
bnad_mem_free(struct bnad *bnad,
	      struct bna_mem_info *mem_info)
{
	int i;
	dma_addr_t dma_pa;

	if (mem_info->mdl == NULL)
		return;

	for (i = 0; i < mem_info->num; i++) {
		if (mem_info->mdl[i].kva != NULL) {
			if (mem_info->mem_type == BNA_MEM_T_DMA) {
				BNA_GET_DMA_ADDR(&(mem_info->mdl[i].dma),
						dma_pa);
				dma_free_coherent(&bnad->pcidev->dev,
						  mem_info->mdl[i].len,
						  mem_info->mdl[i].kva, dma_pa);
			} else
				kfree(mem_info->mdl[i].kva);
		}
	}
	kfree(mem_info->mdl);
	mem_info->mdl = NULL;
}