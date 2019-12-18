#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_8__ {int /*<<< orphan*/  uc; } ;
struct drm_i915_private {TYPE_1__ drm; TYPE_3__ gt; int /*<<< orphan*/  uncore; int /*<<< orphan*/  wopcm; } ;
struct TYPE_7__ {int /*<<< orphan*/  page_sizes; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE_4K ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SZ_256K ; 
 int __intel_engines_record_defaults (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_userptr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_contexts_fini (struct drm_i915_private*) ; 
 int i915_gem_contexts_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_drain_workqueue (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_fini_scratch (struct drm_i915_private*) ; 
 int i915_gem_init_hw (struct drm_i915_private*) ; 
 int i915_gem_init_scratch (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int i915_gem_init_userptr (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_fences (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_restore_gtt_mappings (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend_late (struct drm_i915_private*) ; 
 int i915_ggtt_enable_hw (struct drm_i915_private*) ; 
 int i915_init_ggtt (struct drm_i915_private*) ; 
 int i915_inject_load_error (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  i915_probe_error (struct drm_i915_private*,char*) ; 
 int /*<<< orphan*/  intel_cleanup_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engines_cleanup (struct drm_i915_private*) ; 
 int intel_engines_init (struct drm_i915_private*) ; 
 int intel_engines_setup (struct drm_i915_private*) ; 
 int intel_engines_verify_workarounds (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_is_wedged (TYPE_3__*) ; 
 int intel_gt_resume (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_init_clock_gating (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_timelines_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_timelines_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_cleanup_firmwares (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fetch_firmwares (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fini_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_vgpu_has_huge_gtt (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_wopcm_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* mkwrite_device_info (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_init(struct drm_i915_private *dev_priv)
{
	int ret;

	/* We need to fallback to 4K pages if host doesn't support huge gtt. */
	if (intel_vgpu_active(dev_priv) && !intel_vgpu_has_huge_gtt(dev_priv))
		mkwrite_device_info(dev_priv)->page_sizes =
			I915_GTT_PAGE_SIZE_4K;

	intel_timelines_init(dev_priv);

	ret = i915_gem_init_userptr(dev_priv);
	if (ret)
		return ret;

	intel_uc_fetch_firmwares(&dev_priv->gt.uc);
	intel_wopcm_init(&dev_priv->wopcm);

	/* This is just a security blanket to placate dragons.
	 * On some systems, we very sporadically observe that the first TLBs
	 * used by the CS may be stale, despite us poking the TLB reset. If
	 * we hold the forcewake during initialisation these problems
	 * just magically go away.
	 */
	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	ret = i915_init_ggtt(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_unlock;
	}

	ret = i915_gem_init_scratch(dev_priv,
				    IS_GEN(dev_priv, 2) ? SZ_256K : PAGE_SIZE);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_ggtt;
	}

	ret = intel_engines_setup(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_unlock;
	}

	ret = i915_gem_contexts_init(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_scratch;
	}

	ret = intel_engines_init(dev_priv);
	if (ret) {
		GEM_BUG_ON(ret == -EIO);
		goto err_context;
	}

	intel_init_gt_powersave(dev_priv);

	intel_uc_init(&dev_priv->gt.uc);

	ret = i915_gem_init_hw(dev_priv);
	if (ret)
		goto err_uc_init;

	/* Only when the HW is re-initialised, can we replay the requests */
	ret = intel_gt_resume(&dev_priv->gt);
	if (ret)
		goto err_init_hw;

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

	ret = intel_engines_verify_workarounds(dev_priv);
	if (ret)
		goto err_gt;

	ret = __intel_engines_record_defaults(dev_priv);
	if (ret)
		goto err_gt;

	ret = i915_inject_load_error(dev_priv, -ENODEV);
	if (ret)
		goto err_gt;

	ret = i915_inject_load_error(dev_priv, -EIO);
	if (ret)
		goto err_gt;

	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	return 0;

	/*
	 * Unwinding is complicated by that we want to handle -EIO to mean
	 * disable GPU submission but keep KMS alive. We want to mark the
	 * HW as irrevisibly wedged, but keep enough state around that the
	 * driver doesn't explode during runtime.
	 */
err_gt:
	mutex_unlock(&dev_priv->drm.struct_mutex);

	intel_gt_set_wedged(&dev_priv->gt);
	i915_gem_suspend(dev_priv);
	i915_gem_suspend_late(dev_priv);

	i915_gem_drain_workqueue(dev_priv);

	mutex_lock(&dev_priv->drm.struct_mutex);
err_init_hw:
	intel_uc_fini_hw(&dev_priv->gt.uc);
err_uc_init:
	if (ret != -EIO) {
		intel_uc_fini(&dev_priv->gt.uc);
		intel_cleanup_gt_powersave(dev_priv);
		intel_engines_cleanup(dev_priv);
	}
err_context:
	if (ret != -EIO)
		i915_gem_contexts_fini(dev_priv);
err_scratch:
	i915_gem_fini_scratch(dev_priv);
err_ggtt:
err_unlock:
	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
	mutex_unlock(&dev_priv->drm.struct_mutex);

	if (ret != -EIO) {
		intel_uc_cleanup_firmwares(&dev_priv->gt.uc);
		i915_gem_cleanup_userptr(dev_priv);
		intel_timelines_fini(dev_priv);
	}

	if (ret == -EIO) {
		mutex_lock(&dev_priv->drm.struct_mutex);

		/*
		 * Allow engines or uC initialisation to fail by marking the GPU
		 * as wedged. But we only want to do this when the GPU is angry,
		 * for all other failure, such as an allocation failure, bail.
		 */
		if (!intel_gt_is_wedged(&dev_priv->gt)) {
			i915_probe_error(dev_priv,
					 "Failed to initialize GPU, declaring it wedged!\n");
			intel_gt_set_wedged(&dev_priv->gt);
		}

		/* Minimal basic recovery for KMS */
		ret = i915_ggtt_enable_hw(dev_priv);
		i915_gem_restore_gtt_mappings(dev_priv);
		i915_gem_restore_fences(dev_priv);
		intel_init_clock_gating(dev_priv);

		mutex_unlock(&dev_priv->drm.struct_mutex);
	}

	i915_gem_drain_freed_objects(dev_priv);
	return ret;
}