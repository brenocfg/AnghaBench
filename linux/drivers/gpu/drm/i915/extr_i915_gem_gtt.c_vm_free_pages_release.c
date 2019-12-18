#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pagevec {int nr; int /*<<< orphan*/  pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; struct pagevec pvec; } ;
struct i915_address_space {TYPE_3__ free_pages; TYPE_2__* i915; scalar_t__ pt_kmap_wc; } ;
struct TYPE_4__ {int /*<<< orphan*/  wc_stash; } ;
struct TYPE_5__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int PAGEVEC_SIZE ; 
 int /*<<< orphan*/  __pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_reinit (struct pagevec*) ; 
 int /*<<< orphan*/  set_pages_array_wb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stash_push_pagevec (int /*<<< orphan*/ *,struct pagevec*) ; 

__attribute__((used)) static void vm_free_pages_release(struct i915_address_space *vm,
				  bool immediate)
{
	struct pagevec *pvec = &vm->free_pages.pvec;
	struct pagevec stack;

	lockdep_assert_held(&vm->free_pages.lock);
	GEM_BUG_ON(!pagevec_count(pvec));

	if (vm->pt_kmap_wc) {
		/*
		 * When we use WC, first fill up the global stash and then
		 * only if full immediately free the overflow.
		 */
		stash_push_pagevec(&vm->i915->mm.wc_stash, pvec);

		/*
		 * As we have made some room in the VM's free_pages,
		 * we can wait for it to fill again. Unless we are
		 * inside i915_address_space_fini() and must
		 * immediately release the pages!
		 */
		if (pvec->nr <= (immediate ? 0 : PAGEVEC_SIZE - 1))
			return;

		/*
		 * We have to drop the lock to allow ourselves to sleep,
		 * so take a copy of the pvec and clear the stash for
		 * others to use it as we sleep.
		 */
		stack = *pvec;
		pagevec_reinit(pvec);
		spin_unlock(&vm->free_pages.lock);

		pvec = &stack;
		set_pages_array_wb(pvec->pages, pvec->nr);

		spin_lock(&vm->free_pages.lock);
	}

	__pagevec_release(pvec);
}