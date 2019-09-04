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
struct i915_page_directory_pointer {int dummy; } ;
struct i915_address_space {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct i915_page_directory_pointer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __pdp_fini (struct i915_page_directory_pointer*) ; 
 int __pdp_init (struct i915_address_space*,struct i915_page_directory_pointer*) ; 
 int /*<<< orphan*/  kfree (struct i915_page_directory_pointer*) ; 
 struct i915_page_directory_pointer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int setup_px (struct i915_address_space*,struct i915_page_directory_pointer*) ; 
 int /*<<< orphan*/  use_4lvl (struct i915_address_space*) ; 

__attribute__((used)) static struct i915_page_directory_pointer *
alloc_pdp(struct i915_address_space *vm)
{
	struct i915_page_directory_pointer *pdp;
	int ret = -ENOMEM;

	GEM_BUG_ON(!use_4lvl(vm));

	pdp = kzalloc(sizeof(*pdp), GFP_KERNEL);
	if (!pdp)
		return ERR_PTR(-ENOMEM);

	ret = __pdp_init(vm, pdp);
	if (ret)
		goto fail_bitmap;

	ret = setup_px(vm, pdp);
	if (ret)
		goto fail_page_m;

	return pdp;

fail_page_m:
	__pdp_fini(pdp);
fail_bitmap:
	kfree(pdp);

	return ERR_PTR(ret);
}