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
struct mv_cesa_tdma_desc {struct mv_cesa_tdma_desc* next; int /*<<< orphan*/  next_dma; int /*<<< orphan*/  cur_dma; } ;
struct mv_cesa_tdma_chain {struct mv_cesa_tdma_desc* last; struct mv_cesa_tdma_desc* first; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  tdma_desc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mv_cesa_tdma_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* cesa_dev ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct mv_cesa_tdma_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mv_cesa_tdma_desc *
mv_cesa_dma_add_desc(struct mv_cesa_tdma_chain *chain, gfp_t flags)
{
	struct mv_cesa_tdma_desc *new_tdma = NULL;
	dma_addr_t dma_handle;

	new_tdma = dma_pool_zalloc(cesa_dev->dma->tdma_desc_pool, flags,
				   &dma_handle);
	if (!new_tdma)
		return ERR_PTR(-ENOMEM);

	new_tdma->cur_dma = dma_handle;
	if (chain->last) {
		chain->last->next_dma = cpu_to_le32(dma_handle);
		chain->last->next = new_tdma;
	} else {
		chain->first = new_tdma;
	}

	chain->last = new_tdma;

	return new_tdma;
}