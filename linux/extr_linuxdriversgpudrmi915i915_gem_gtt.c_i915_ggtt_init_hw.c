#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  color_adjust; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* cleanup ) (TYPE_5__*) ;TYPE_2__ mm; int /*<<< orphan*/  has_read_only; } ;
struct TYPE_10__ {int /*<<< orphan*/  start; } ;
struct i915_ggtt {TYPE_5__ vm; int /*<<< orphan*/  mappable_end; TYPE_4__ gmadr; int /*<<< orphan*/  mtrr; int /*<<< orphan*/  iomap; } ;
struct TYPE_9__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  wc_stash; } ;
struct drm_i915_private {struct i915_ggtt ggtt; TYPE_3__ drm; TYPE_1__ mm; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HAS_LLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  USES_PPGTT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_address_space_init (TYPE_5__*,struct drm_i915_private*) ; 
 int i915_gem_init_stolen (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gtt_color_adjust ; 
 int /*<<< orphan*/  io_mapping_init_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

int i915_ggtt_init_hw(struct drm_i915_private *dev_priv)
{
	struct i915_ggtt *ggtt = &dev_priv->ggtt;
	int ret;

	stash_init(&dev_priv->mm.wc_stash);

	/* Note that we use page colouring to enforce a guard page at the
	 * end of the address space. This is required as the CS may prefetch
	 * beyond the end of the batch buffer, across the page boundary,
	 * and beyond the end of the GTT if we do not provide a guard.
	 */
	mutex_lock(&dev_priv->drm.struct_mutex);
	i915_address_space_init(&ggtt->vm, dev_priv);

	/* Only VLV supports read-only GGTT mappings */
	ggtt->vm.has_read_only = IS_VALLEYVIEW(dev_priv);

	if (!HAS_LLC(dev_priv) && !USES_PPGTT(dev_priv))
		ggtt->vm.mm.color_adjust = i915_gtt_color_adjust;
	mutex_unlock(&dev_priv->drm.struct_mutex);

	if (!io_mapping_init_wc(&dev_priv->ggtt.iomap,
				dev_priv->ggtt.gmadr.start,
				dev_priv->ggtt.mappable_end)) {
		ret = -EIO;
		goto out_gtt_cleanup;
	}

	ggtt->mtrr = arch_phys_wc_add(ggtt->gmadr.start, ggtt->mappable_end);

	/*
	 * Initialise stolen early so that we may reserve preallocated
	 * objects for the BIOS to KMS transition.
	 */
	ret = i915_gem_init_stolen(dev_priv);
	if (ret)
		goto out_gtt_cleanup;

	return 0;

out_gtt_cleanup:
	ggtt->vm.cleanup(&ggtt->vm);
	return ret;
}