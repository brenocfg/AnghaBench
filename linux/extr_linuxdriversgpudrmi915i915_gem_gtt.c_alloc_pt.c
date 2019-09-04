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
struct i915_page_table {scalar_t__ used_ptes; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_page_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_GFP_ALLOW_FAIL ; 
 int /*<<< orphan*/  kfree (struct i915_page_table*) ; 
 struct i915_page_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int setup_px (struct i915_address_space*,struct i915_page_table*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct i915_page_table *alloc_pt(struct i915_address_space *vm)
{
	struct i915_page_table *pt;

	pt = kmalloc(sizeof(*pt), I915_GFP_ALLOW_FAIL);
	if (unlikely(!pt))
		return ERR_PTR(-ENOMEM);

	if (unlikely(setup_px(vm, pt))) {
		kfree(pt);
		return ERR_PTR(-ENOMEM);
	}

	pt->used_ptes = 0;
	return pt;
}