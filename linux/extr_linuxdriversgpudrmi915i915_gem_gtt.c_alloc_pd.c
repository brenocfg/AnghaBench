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
struct i915_page_directory {scalar_t__ used_pdes; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_page_directory* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_GFP_ALLOW_FAIL ; 
 int /*<<< orphan*/  kfree (struct i915_page_directory*) ; 
 struct i915_page_directory* kzalloc (int,int /*<<< orphan*/ ) ; 
 int setup_px (struct i915_address_space*,struct i915_page_directory*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct i915_page_directory *alloc_pd(struct i915_address_space *vm)
{
	struct i915_page_directory *pd;

	pd = kzalloc(sizeof(*pd), I915_GFP_ALLOW_FAIL);
	if (unlikely(!pd))
		return ERR_PTR(-ENOMEM);

	if (unlikely(setup_px(vm, pd))) {
		kfree(pd);
		return ERR_PTR(-ENOMEM);
	}

	pd->used_pdes = 0;
	return pd;
}