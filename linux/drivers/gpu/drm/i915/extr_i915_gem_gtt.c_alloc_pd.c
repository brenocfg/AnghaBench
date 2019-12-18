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
struct i915_page_directory {int dummy; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_page_directory* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct i915_page_directory* __alloc_pd (int) ; 
 int /*<<< orphan*/  kfree (struct i915_page_directory*) ; 
 int /*<<< orphan*/  px_base (struct i915_page_directory*) ; 
 int setup_page_dma (struct i915_address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct i915_page_directory *alloc_pd(struct i915_address_space *vm)
{
	struct i915_page_directory *pd;

	pd = __alloc_pd(sizeof(*pd));
	if (unlikely(!pd))
		return ERR_PTR(-ENOMEM);

	if (unlikely(setup_page_dma(vm, px_base(pd)))) {
		kfree(pd);
		return ERR_PTR(-ENOMEM);
	}

	return pd;
}