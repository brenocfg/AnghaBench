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
struct vmw_validation_context {unsigned int mem_size_left; unsigned int vm_size_left; unsigned int page_address; int /*<<< orphan*/  page_list; TYPE_1__* vm; int /*<<< orphan*/  total_mem; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int (* reserve_mem ) (TYPE_1__*,scalar_t__) ;scalar_t__ gran; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int page_address (struct page*) ; 
 int stub1 (TYPE_1__*,scalar_t__) ; 
 unsigned int vmw_validation_align (unsigned int) ; 

void *vmw_validation_mem_alloc(struct vmw_validation_context *ctx,
			       unsigned int size)
{
	void *addr;

	size = vmw_validation_align(size);
	if (size > PAGE_SIZE)
		return NULL;

	if (ctx->mem_size_left < size) {
		struct page *page;

		if (ctx->vm && ctx->vm_size_left < PAGE_SIZE) {
			int ret = ctx->vm->reserve_mem(ctx->vm, ctx->vm->gran);

			if (ret)
				return NULL;

			ctx->vm_size_left += ctx->vm->gran;
			ctx->total_mem += ctx->vm->gran;
		}

		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		if (!page)
			return NULL;

		if (ctx->vm)
			ctx->vm_size_left -= PAGE_SIZE;

		list_add_tail(&page->lru, &ctx->page_list);
		ctx->page_address = page_address(page);
		ctx->mem_size_left = PAGE_SIZE;
	}

	addr = (void *) (ctx->page_address + (PAGE_SIZE - ctx->mem_size_left));
	ctx->mem_size_left -= size;

	return addr;
}