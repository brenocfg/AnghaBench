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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pvec; } ;
struct i915_address_space {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mm; TYPE_1__ free_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (scalar_t__) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pagevec_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_free_pages_release (struct i915_address_space*,int) ; 

__attribute__((used)) static void i915_address_space_fini(struct i915_address_space *vm)
{
	spin_lock(&vm->free_pages.lock);
	if (pagevec_count(&vm->free_pages.pvec))
		vm_free_pages_release(vm, true);
	GEM_BUG_ON(pagevec_count(&vm->free_pages.pvec));
	spin_unlock(&vm->free_pages.lock);

	drm_mm_takedown(&vm->mm);

	mutex_destroy(&vm->mutex);
}