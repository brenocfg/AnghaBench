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
struct i915_page_table {int /*<<< orphan*/  used; int /*<<< orphan*/  base; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_page_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_GFP_ALLOW_FAIL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i915_page_table*) ; 
 struct i915_page_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int setup_page_dma (struct i915_address_space*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct i915_page_table *alloc_pt(struct i915_address_space *vm)
{
	struct i915_page_table *pt;

	pt = kmalloc(sizeof(*pt), I915_GFP_ALLOW_FAIL);
	if (unlikely(!pt))
		return ERR_PTR(-ENOMEM);

	if (unlikely(setup_page_dma(vm, &pt->base))) {
		kfree(pt);
		return ERR_PTR(-ENOMEM);
	}

	atomic_set(&pt->used, 0);
	return pt;
}