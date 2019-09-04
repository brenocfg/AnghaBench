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
struct mdc_tx_desc {int /*<<< orphan*/  list_phys; struct mdc_hw_list_desc* list; TYPE_1__* chan; } ;
struct mdc_hw_list_desc {int /*<<< orphan*/  node_addr; struct mdc_hw_list_desc* next_desc; } ;
struct mdc_dma {int /*<<< orphan*/  desc_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct mdc_dma* mdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct mdc_hw_list_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdc_list_desc_free(struct mdc_tx_desc *mdesc)
{
	struct mdc_dma *mdma = mdesc->chan->mdma;
	struct mdc_hw_list_desc *curr, *next;
	dma_addr_t curr_phys, next_phys;

	curr = mdesc->list;
	curr_phys = mdesc->list_phys;
	while (curr) {
		next = curr->next_desc;
		next_phys = curr->node_addr;
		dma_pool_free(mdma->desc_pool, curr, curr_phys);
		curr = next;
		curr_phys = next_phys;
	}
}