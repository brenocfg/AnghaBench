#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  cleanup_engine; int /*<<< orphan*/  resume; } ;
struct TYPE_5__ {int /*<<< orphan*/  unordered_timeline; } ;
struct drm_i915_private {int /*<<< orphan*/  gpu_error; TYPE_3__ drm; int /*<<< orphan*/  wopcm; TYPE_2__ gt; TYPE_1__ mm; } ;
struct TYPE_8__ {int /*<<< orphan*/  page_sizes; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ HAS_LOGICAL_RING_CONTEXTS (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_4K ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __intel_engines_record_defaults (struct drm_i915_private*) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  i915_gem_cleanup_engines (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_userptr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_contexts_fini (struct drm_i915_private*) ; 
 int i915_gem_contexts_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_workqueue (struct drm_i915_private*) ; 
 int i915_gem_init_ggtt (struct drm_i915_private*) ; 
 int i915_gem_init_hw (struct drm_i915_private*) ; 
 int i915_gem_init_userptr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_set_wedged (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend_late (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_load_failure () ; 
 int /*<<< orphan*/  i915_load_error (struct drm_i915_private*,char*) ; 
 int /*<<< orphan*/  i915_terminally_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_cleanup_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engine_cleanup ; 
 int intel_engines_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_clock_gating (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_legacy_submission_resume ; 
 int /*<<< orphan*/  intel_logical_ring_cleanup ; 
 int /*<<< orphan*/  intel_lr_context_resume ; 
 int /*<<< orphan*/  intel_uc_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini_misc (struct drm_i915_private*) ; 
 int intel_uc_init (struct drm_i915_private*) ; 
 int intel_uc_init_misc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_vgpu_has_huge_gtt (struct drm_i915_private*) ; 
 int intel_wopcm_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* mkwrite_device_info (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_init(struct drm_i915_private *dev_priv)
{
	int ret;

	/* We need to fallback to 4K pages if host doesn't support huge gtt. */
	if (intel_vgpu_active(dev_priv) && !intel_vgpu_has_huge_gtt(dev_priv))
		mkwrite_device_info(dev_priv)->page_sizes =
			I915_GTT_PAGE_SIZE_4K;

	dev_priv->mm.unordered_timeline = dma_fence_context_alloc(1);

	if (HAS_LOGICAL_RING_CONTEXTS(dev_priv)) {
		dev_priv->gt.resume = intel_lr_context_resume;
		dev_priv->gt.cleanup_engine = intel_logical_ring_cleanup;
	} else {
		dev_priv->gt.resume = intel_legacy_submission_resume;
		dev_priv->gt.cleanup_engine = intel_engine_cleanup;
	}

	ret = i915_gem_init_userptr(dev_priv);
	if (ret)
		return ret;

	ret = intel_uc_init_misc(dev_priv);
	if (ret)
		return ret;

	ret = intel_wopcm_init(&dev_priv->wopcm);
	if (ret)
		goto err_uc_misc;

	/* This is just a security blanket to placate dragons.
	 * On some systems, we very sporadically observe that the first TLBs
	 * used by the CS may be stale, despite us poking the TLB reset. If
	 * we hold the forcewake during initialisation these problems
	 * just magically go away.
	 */
	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_ALL);

	ret = i915_gem_init_ggtt(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_unlock;
	}

	ret = i915_gem_contexts_init(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_ggtt;
	}

	ret = intel_engines_init(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_context;
	}

	intel_init_gt_powersave(dev_priv);

	ret = intel_uc_init(dev_priv);
	if (ret)
		goto err_pm;

	ret = i915_gem_init_hw(dev_priv);
	if (ret)
		goto err_uc_init;

	/*
	 * Despite its name intel_init_clock_gating applies both display
	 * clock gating workarounds; GT mmio workarounds and the occasional
	 * GT power context workaround. Worse, sometimes it includes a context
	 * register workaround which we need to apply before we record the
	 * default HW state for all contexts.
	 *
	 * FIXME: break up the workarounds and apply them at the right time!
	 */
	intel_init_clock_gating(dev_priv);

	ret = __intel_engines_record_defaults(dev_priv);
	if (ret)
		goto err_init_hw;

	if (i915_inject_load_failure()) {
		ret = -ENODEV;
		goto err_init_hw;
	}

	if (i915_inject_load_failure()) {
		ret = -EIO;
		goto err_init_hw;
	}

	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	return 0;

	/*
	 * Unwinding is complicated by that we want to handle -EIO to mean
	 * disable GPU submission but keep KMS alive. We want to mark the
	 * HW as irrevisibly wedged, but keep enough state around that the
	 * driver doesn't explode during runtime.
	 */
err_init_hw:
	mutex_unlock(&dev_priv->drm.struct_mutex);

	WARN_ON(i915_gem_suspend(dev_priv));
	i915_gem_suspend_late(dev_priv);

	i915_gem_drain_workqueue(dev_priv);

	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_uc_fini_hw(dev_priv);
err_uc_init:
	intel_uc_fini(dev_priv);
err_pm:
	if (ret != -EIO) {
		intel_cleanup_gt_powersave(dev_priv);
		i915_gem_cleanup_engines(dev_priv);
	}
err_context:
	if (ret != -EIO)
		i915_gem_contexts_fini(dev_priv);
err_ggtt:
err_unlock:
	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);
	mutex_unlock(&dev_priv->drm.struct_mutex);

err_uc_misc:
	intel_uc_fini_misc(dev_priv);

	if (ret != -EIO)
		i915_gem_cleanup_userptr(dev_priv);

	if (ret == -EIO) {
		/*
		 * Allow engine initialisation to fail by marking the GPU as
		 * wedged. But we only want to do this where the GPU is angry,
		 * for all other failure, such as an allocation failure, bail.
		 */
		if (!i915_terminally_wedged(&dev_priv->gpu_error)) {
			i915_load_error(dev_priv,
					"Failed to initialize GPU, declaring it wedged!\n");
			i915_gem_set_wedged(dev_priv);
		}
		ret = 0;
	}

	i915_gem_drain_freed_objects(dev_priv);
	return ret;
}