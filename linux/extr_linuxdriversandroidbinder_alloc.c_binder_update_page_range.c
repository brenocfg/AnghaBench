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
struct vm_area_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct binder_lru_page {int /*<<< orphan*/ * page_ptr; int /*<<< orphan*/  lru; struct binder_alloc* alloc; } ;
struct binder_alloc {void* buffer; uintptr_t user_buffer_offset; size_t pages_high; struct binder_lru_page* pages; int /*<<< orphan*/  pid; struct vm_area_struct* vma; struct mm_struct* vma_vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_BUFFER_ALLOC ; 
 int /*<<< orphan*/  BINDER_DEBUG_USER_ERROR ; 
 int ENOMEM ; 
 int ESRCH ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __GFP_HIGHMEM ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alloc_page (int) ; 
 int /*<<< orphan*/  binder_alloc_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  binder_alloc_lru ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cache_vmap (unsigned long,unsigned long) ; 
 int list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int map_kernel_range_noflush (unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ mmget_not_zero (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_binder_alloc_lru_end (struct binder_alloc*,size_t) ; 
 int /*<<< orphan*/  trace_binder_alloc_lru_start (struct binder_alloc*,size_t) ; 
 int /*<<< orphan*/  trace_binder_alloc_page_end (struct binder_alloc*,size_t) ; 
 int /*<<< orphan*/  trace_binder_alloc_page_start (struct binder_alloc*,size_t) ; 
 int /*<<< orphan*/  trace_binder_free_lru_end (struct binder_alloc*,size_t) ; 
 int /*<<< orphan*/  trace_binder_free_lru_start (struct binder_alloc*,size_t) ; 
 int /*<<< orphan*/  trace_binder_update_page_range (struct binder_alloc*,int,void*,void*) ; 
 int /*<<< orphan*/  unmap_kernel_range (unsigned long,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binder_update_page_range(struct binder_alloc *alloc, int allocate,
				    void *start, void *end)
{
	void *page_addr;
	unsigned long user_page_addr;
	struct binder_lru_page *page;
	struct vm_area_struct *vma = NULL;
	struct mm_struct *mm = NULL;
	bool need_mm = false;

	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: %s pages %pK-%pK\n", alloc->pid,
		     allocate ? "allocate" : "free", start, end);

	if (end <= start)
		return 0;

	trace_binder_update_page_range(alloc, allocate, start, end);

	if (allocate == 0)
		goto free_range;

	for (page_addr = start; page_addr < end; page_addr += PAGE_SIZE) {
		page = &alloc->pages[(page_addr - alloc->buffer) / PAGE_SIZE];
		if (!page->page_ptr) {
			need_mm = true;
			break;
		}
	}

	if (need_mm && mmget_not_zero(alloc->vma_vm_mm))
		mm = alloc->vma_vm_mm;

	if (mm) {
		down_read(&mm->mmap_sem);
		vma = alloc->vma;
	}

	if (!vma && need_mm) {
		binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
				   "%d: binder_alloc_buf failed to map pages in userspace, no vma\n",
				   alloc->pid);
		goto err_no_vma;
	}

	for (page_addr = start; page_addr < end; page_addr += PAGE_SIZE) {
		int ret;
		bool on_lru;
		size_t index;

		index = (page_addr - alloc->buffer) / PAGE_SIZE;
		page = &alloc->pages[index];

		if (page->page_ptr) {
			trace_binder_alloc_lru_start(alloc, index);

			on_lru = list_lru_del(&binder_alloc_lru, &page->lru);
			WARN_ON(!on_lru);

			trace_binder_alloc_lru_end(alloc, index);
			continue;
		}

		if (WARN_ON(!vma))
			goto err_page_ptr_cleared;

		trace_binder_alloc_page_start(alloc, index);
		page->page_ptr = alloc_page(GFP_KERNEL |
					    __GFP_HIGHMEM |
					    __GFP_ZERO);
		if (!page->page_ptr) {
			pr_err("%d: binder_alloc_buf failed for page at %pK\n",
				alloc->pid, page_addr);
			goto err_alloc_page_failed;
		}
		page->alloc = alloc;
		INIT_LIST_HEAD(&page->lru);

		ret = map_kernel_range_noflush((unsigned long)page_addr,
					       PAGE_SIZE, PAGE_KERNEL,
					       &page->page_ptr);
		flush_cache_vmap((unsigned long)page_addr,
				(unsigned long)page_addr + PAGE_SIZE);
		if (ret != 1) {
			pr_err("%d: binder_alloc_buf failed to map page at %pK in kernel\n",
			       alloc->pid, page_addr);
			goto err_map_kernel_failed;
		}
		user_page_addr =
			(uintptr_t)page_addr + alloc->user_buffer_offset;
		ret = vm_insert_page(vma, user_page_addr, page[0].page_ptr);
		if (ret) {
			pr_err("%d: binder_alloc_buf failed to map page at %lx in userspace\n",
			       alloc->pid, user_page_addr);
			goto err_vm_insert_page_failed;
		}

		if (index + 1 > alloc->pages_high)
			alloc->pages_high = index + 1;

		trace_binder_alloc_page_end(alloc, index);
		/* vm_insert_page does not seem to increment the refcount */
	}
	if (mm) {
		up_read(&mm->mmap_sem);
		mmput(mm);
	}
	return 0;

free_range:
	for (page_addr = end - PAGE_SIZE; page_addr >= start;
	     page_addr -= PAGE_SIZE) {
		bool ret;
		size_t index;

		index = (page_addr - alloc->buffer) / PAGE_SIZE;
		page = &alloc->pages[index];

		trace_binder_free_lru_start(alloc, index);

		ret = list_lru_add(&binder_alloc_lru, &page->lru);
		WARN_ON(!ret);

		trace_binder_free_lru_end(alloc, index);
		continue;

err_vm_insert_page_failed:
		unmap_kernel_range((unsigned long)page_addr, PAGE_SIZE);
err_map_kernel_failed:
		__free_page(page->page_ptr);
		page->page_ptr = NULL;
err_alloc_page_failed:
err_page_ptr_cleared:
		;
	}
err_no_vma:
	if (mm) {
		up_read(&mm->mmap_sem);
		mmput(mm);
	}
	return vma ? -ENOMEM : -ESRCH;
}