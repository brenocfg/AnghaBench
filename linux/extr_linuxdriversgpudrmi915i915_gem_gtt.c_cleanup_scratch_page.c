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
struct i915_page_dma {int /*<<< orphan*/  order; int /*<<< orphan*/  page; int /*<<< orphan*/  daddr; } ;
struct i915_address_space {int /*<<< orphan*/  dma; struct i915_page_dma scratch_page; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_scratch_page(struct i915_address_space *vm)
{
	struct i915_page_dma *p = &vm->scratch_page;

	dma_unmap_page(vm->dma, p->daddr, BIT(p->order) << PAGE_SHIFT,
		       PCI_DMA_BIDIRECTIONAL);
	__free_pages(p->page, p->order);
}