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
struct TYPE_3__ {int /*<<< orphan*/  clear_pages; int /*<<< orphan*/  set_pages; int /*<<< orphan*/  unbind_vma; int /*<<< orphan*/  bind_vma; } ;
struct TYPE_4__ {TYPE_1__ vma_ops; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  insert_entries; int /*<<< orphan*/  insert_page; int /*<<< orphan*/  clear_range; int /*<<< orphan*/  file; int /*<<< orphan*/  total; struct drm_i915_private* i915; } ;
struct i915_ppgtt {TYPE_2__ vm; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  VM_CLASS_PPGTT ; 
 int /*<<< orphan*/  clear_pages ; 
 int /*<<< orphan*/  i915_address_space_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct i915_ppgtt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_bind_ppgtt ; 
 int /*<<< orphan*/  mock_cleanup ; 
 int /*<<< orphan*/  mock_insert_entries ; 
 int /*<<< orphan*/  mock_insert_page ; 
 int /*<<< orphan*/  mock_unbind_ppgtt ; 
 int /*<<< orphan*/  nop_clear_range ; 
 int /*<<< orphan*/  ppgtt_set_pages ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct i915_ppgtt *mock_ppgtt(struct drm_i915_private *i915, const char *name)
{
	struct i915_ppgtt *ppgtt;

	ppgtt = kzalloc(sizeof(*ppgtt), GFP_KERNEL);
	if (!ppgtt)
		return NULL;

	ppgtt->vm.i915 = i915;
	ppgtt->vm.total = round_down(U64_MAX, PAGE_SIZE);
	ppgtt->vm.file = ERR_PTR(-ENODEV);

	i915_address_space_init(&ppgtt->vm, VM_CLASS_PPGTT);

	ppgtt->vm.clear_range = nop_clear_range;
	ppgtt->vm.insert_page = mock_insert_page;
	ppgtt->vm.insert_entries = mock_insert_entries;
	ppgtt->vm.cleanup = mock_cleanup;

	ppgtt->vm.vma_ops.bind_vma    = mock_bind_ppgtt;
	ppgtt->vm.vma_ops.unbind_vma  = mock_unbind_ppgtt;
	ppgtt->vm.vma_ops.set_pages   = ppgtt_set_pages;
	ppgtt->vm.vma_ops.clear_pages = clear_pages;

	return ppgtt;
}