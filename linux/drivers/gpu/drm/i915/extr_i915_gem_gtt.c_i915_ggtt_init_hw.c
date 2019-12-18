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
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
struct TYPE_6__ {TYPE_2__ vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  wc_stash; } ;
struct drm_i915_private {TYPE_3__ ggtt; TYPE_1__ mm; } ;

/* Variables and functions */
 int ggtt_init_hw (TYPE_3__*) ; 
 int i915_gem_init_stolen (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int i915_ggtt_init_hw(struct drm_i915_private *dev_priv)
{
	int ret;

	stash_init(&dev_priv->mm.wc_stash);

	/* Note that we use page colouring to enforce a guard page at the
	 * end of the address space. This is required as the CS may prefetch
	 * beyond the end of the batch buffer, across the page boundary,
	 * and beyond the end of the GTT if we do not provide a guard.
	 */
	ret = ggtt_init_hw(&dev_priv->ggtt);
	if (ret)
		return ret;

	/*
	 * Initialise stolen early so that we may reserve preallocated
	 * objects for the BIOS to KMS transition.
	 */
	ret = i915_gem_init_stolen(dev_priv);
	if (ret)
		goto out_gtt_cleanup;

	return 0;

out_gtt_cleanup:
	dev_priv->ggtt.vm.cleanup(&dev_priv->ggtt.vm);
	return ret;
}