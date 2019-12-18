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
struct TYPE_4__ {int top; int /*<<< orphan*/  pte_encode; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  insert_entries; int /*<<< orphan*/  clear_range; int /*<<< orphan*/  allocate_va_range; } ;
struct i915_ppgtt {struct gen6_ppgtt* pd; TYPE_2__ vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  pte_encode; } ;
struct i915_ggtt {TYPE_1__ vm; } ;
struct gen6_ppgtt {struct i915_ppgtt base; int /*<<< orphan*/  vma; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct i915_ppgtt* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEN6_PD_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct gen6_ppgtt* __alloc_pd (int) ; 
 int /*<<< orphan*/  free_scratch (TYPE_2__*) ; 
 int /*<<< orphan*/  gen6_alloc_va_range ; 
 int /*<<< orphan*/  gen6_ppgtt_cleanup ; 
 int /*<<< orphan*/  gen6_ppgtt_clear_range ; 
 int gen6_ppgtt_init_scratch (struct gen6_ppgtt*) ; 
 int /*<<< orphan*/  gen6_ppgtt_insert_entries ; 
 int /*<<< orphan*/  kfree (struct gen6_ppgtt*) ; 
 struct gen6_ppgtt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_vma_create (struct gen6_ppgtt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppgtt_init (struct i915_ppgtt*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i915_ppgtt *gen6_ppgtt_create(struct drm_i915_private *i915)
{
	struct i915_ggtt * const ggtt = &i915->ggtt;
	struct gen6_ppgtt *ppgtt;
	int err;

	ppgtt = kzalloc(sizeof(*ppgtt), GFP_KERNEL);
	if (!ppgtt)
		return ERR_PTR(-ENOMEM);

	ppgtt_init(&ppgtt->base, &i915->gt);
	ppgtt->base.vm.top = 1;

	ppgtt->base.vm.allocate_va_range = gen6_alloc_va_range;
	ppgtt->base.vm.clear_range = gen6_ppgtt_clear_range;
	ppgtt->base.vm.insert_entries = gen6_ppgtt_insert_entries;
	ppgtt->base.vm.cleanup = gen6_ppgtt_cleanup;

	ppgtt->base.vm.pte_encode = ggtt->vm.pte_encode;

	ppgtt->base.pd = __alloc_pd(sizeof(*ppgtt->base.pd));
	if (!ppgtt->base.pd) {
		err = -ENOMEM;
		goto err_free;
	}

	err = gen6_ppgtt_init_scratch(ppgtt);
	if (err)
		goto err_pd;

	ppgtt->vma = pd_vma_create(ppgtt, GEN6_PD_SIZE);
	if (IS_ERR(ppgtt->vma)) {
		err = PTR_ERR(ppgtt->vma);
		goto err_scratch;
	}

	return &ppgtt->base;

err_scratch:
	free_scratch(&ppgtt->base.vm);
err_pd:
	kfree(ppgtt->base.pd);
err_free:
	kfree(ppgtt);
	return ERR_PTR(err);
}