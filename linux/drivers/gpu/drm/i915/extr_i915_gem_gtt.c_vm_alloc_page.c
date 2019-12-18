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
struct pagevec {size_t nr; struct page** pages; } ;
struct page {int dummy; } ;
struct i915_address_space {int /*<<< orphan*/  free_pages; TYPE_2__* i915; int /*<<< orphan*/  pt_kmap_wc; int /*<<< orphan*/  fault_attr; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_stash; } ;
struct TYPE_4__ {TYPE_1__ mm; } ;

/* Variables and functions */
 scalar_t__ I915_SELFTEST_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pagevec_release (struct pagevec*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_shrink_all (TYPE_2__*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 scalar_t__ pagevec_space (struct pagevec*) ; 
 int /*<<< orphan*/  set_pages_array_wb (struct page**,int) ; 
 int /*<<< orphan*/  set_pages_array_wc (struct page**,size_t) ; 
 int /*<<< orphan*/  should_fail (int /*<<< orphan*/ *,int) ; 
 struct page* stash_pop_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stash_push_pagevec (int /*<<< orphan*/ *,struct pagevec*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct page *vm_alloc_page(struct i915_address_space *vm, gfp_t gfp)
{
	struct pagevec stack;
	struct page *page;

	if (I915_SELFTEST_ONLY(should_fail(&vm->fault_attr, 1)))
		i915_gem_shrink_all(vm->i915);

	page = stash_pop_page(&vm->free_pages);
	if (page)
		return page;

	if (!vm->pt_kmap_wc)
		return alloc_page(gfp);

	/* Look in our global stash of WC pages... */
	page = stash_pop_page(&vm->i915->mm.wc_stash);
	if (page)
		return page;

	/*
	 * Otherwise batch allocate pages to amortize cost of set_pages_wc.
	 *
	 * We have to be careful as page allocation may trigger the shrinker
	 * (via direct reclaim) which will fill up the WC stash underneath us.
	 * So we add our WB pages into a temporary pvec on the stack and merge
	 * them into the WC stash after all the allocations are complete.
	 */
	pagevec_init(&stack);
	do {
		struct page *page;

		page = alloc_page(gfp);
		if (unlikely(!page))
			break;

		stack.pages[stack.nr++] = page;
	} while (pagevec_space(&stack));

	if (stack.nr && !set_pages_array_wc(stack.pages, stack.nr)) {
		page = stack.pages[--stack.nr];

		/* Merge spare WC pages to the global stash */
		if (stack.nr)
			stash_push_pagevec(&vm->i915->mm.wc_stash, &stack);

		/* Push any surplus WC pages onto the local VM stash */
		if (stack.nr)
			stash_push_pagevec(&vm->free_pages, &stack);
	}

	/* Return unwanted leftovers */
	if (unlikely(stack.nr)) {
		WARN_ON_ONCE(set_pages_array_wb(stack.pages, stack.nr));
		__pagevec_release(&stack);
	}

	return page;
}