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
struct vmw_sg_table {int mode; TYPE_1__* sgt; int /*<<< orphan*/  pages; int /*<<< orphan*/  addrs; int /*<<< orphan*/  num_pages; } ;
struct vmw_piter {unsigned long i; int /*<<< orphan*/  iter; int /*<<< orphan*/ * page; int /*<<< orphan*/ * dma_address; int /*<<< orphan*/ * next; int /*<<< orphan*/  pages; int /*<<< orphan*/  addrs; int /*<<< orphan*/  num_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __sg_page_iter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __vmw_piter_dma_addr ; 
 int /*<<< orphan*/  __vmw_piter_non_sg_next ; 
 int /*<<< orphan*/  __vmw_piter_non_sg_page ; 
 int /*<<< orphan*/  __vmw_piter_phys_addr ; 
 int /*<<< orphan*/  __vmw_piter_sg_addr ; 
 int /*<<< orphan*/  __vmw_piter_sg_next ; 
 int /*<<< orphan*/  __vmw_piter_sg_page ; 
#define  vmw_dma_alloc_coherent 131 
#define  vmw_dma_map_bind 130 
#define  vmw_dma_map_populate 129 
#define  vmw_dma_phys 128 

void vmw_piter_start(struct vmw_piter *viter, const struct vmw_sg_table *vsgt,
		     unsigned long p_offset)
{
	viter->i = p_offset - 1;
	viter->num_pages = vsgt->num_pages;
	switch (vsgt->mode) {
	case vmw_dma_phys:
		viter->next = &__vmw_piter_non_sg_next;
		viter->dma_address = &__vmw_piter_phys_addr;
		viter->page = &__vmw_piter_non_sg_page;
		viter->pages = vsgt->pages;
		break;
	case vmw_dma_alloc_coherent:
		viter->next = &__vmw_piter_non_sg_next;
		viter->dma_address = &__vmw_piter_dma_addr;
		viter->page = &__vmw_piter_non_sg_page;
		viter->addrs = vsgt->addrs;
		viter->pages = vsgt->pages;
		break;
	case vmw_dma_map_populate:
	case vmw_dma_map_bind:
		viter->next = &__vmw_piter_sg_next;
		viter->dma_address = &__vmw_piter_sg_addr;
		viter->page = &__vmw_piter_sg_page;
		__sg_page_iter_start(&viter->iter, vsgt->sgt->sgl,
				     vsgt->sgt->orig_nents, p_offset);
		break;
	default:
		BUG();
	}
}