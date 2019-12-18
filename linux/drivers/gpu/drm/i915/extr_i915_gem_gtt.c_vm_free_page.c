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
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pvec; } ;
struct i915_address_space {TYPE_1__ free_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ PAGEVEC_SIZE ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pagevec_add (int /*<<< orphan*/ *,struct page*) ; 
 scalar_t__ pagevec_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagevec_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_free_pages_release (struct i915_address_space*,int) ; 

__attribute__((used)) static void vm_free_page(struct i915_address_space *vm, struct page *page)
{
	/*
	 * On !llc, we need to change the pages back to WB. We only do so
	 * in bulk, so we rarely need to change the page attributes here,
	 * but doing so requires a stop_machine() from deep inside arch/x86/mm.
	 * To make detection of the possible sleep more likely, use an
	 * unconditional might_sleep() for everybody.
	 */
	might_sleep();
	spin_lock(&vm->free_pages.lock);
	while (!pagevec_space(&vm->free_pages.pvec))
		vm_free_pages_release(vm, false);
	GEM_BUG_ON(pagevec_count(&vm->free_pages.pvec) >= PAGEVEC_SIZE);
	pagevec_add(&vm->free_pages.pvec, page);
	spin_unlock(&vm->free_pages.lock);
}