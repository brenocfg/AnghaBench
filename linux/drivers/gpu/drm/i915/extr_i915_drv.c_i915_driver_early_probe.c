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
struct TYPE_4__ {int /*<<< orphan*/  wm_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; int /*<<< orphan*/  wopcm; int /*<<< orphan*/  runtime_pm; int /*<<< orphan*/  hdcp_comp_mutex; int /*<<< orphan*/  pps_mutex; TYPE_2__ wm; int /*<<< orphan*/  av_mutex; int /*<<< orphan*/  sb_qos; int /*<<< orphan*/  sb_lock; int /*<<< orphan*/  backlight_lock; TYPE_1__ gpu_error; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  uncore; int /*<<< orphan*/  mmio_debug; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  i915_gem_cleanup_early (struct drm_i915_private*) ; 
 int i915_gem_init_early (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_probe_failure (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_memcpy_init_early (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_workqueues_cleanup (struct drm_i915_private*) ; 
 int i915_workqueues_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_detect_pch (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_detect_preproduction_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_device_info_subplatform_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_crc_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_driver_late_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_init_early (int /*<<< orphan*/ *,struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_audio_hooks (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_clock_gating_hooks (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_display_hooks (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_dpio (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_irq_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_pm_setup (struct drm_i915_private*) ; 
 int intel_power_domains_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_init_early (int /*<<< orphan*/ *,struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_mmio_debug_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_wopcm_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vlv_alloc_s0ix_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_free_s0ix_state (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_driver_early_probe(struct drm_i915_private *dev_priv)
{
	int ret = 0;

	if (i915_inject_probe_failure(dev_priv))
		return -ENODEV;

	intel_device_info_subplatform_init(dev_priv);

	intel_uncore_mmio_debug_init_early(&dev_priv->mmio_debug);
	intel_uncore_init_early(&dev_priv->uncore, dev_priv);

	spin_lock_init(&dev_priv->irq_lock);
	spin_lock_init(&dev_priv->gpu_error.lock);
	mutex_init(&dev_priv->backlight_lock);

	mutex_init(&dev_priv->sb_lock);
	pm_qos_add_request(&dev_priv->sb_qos,
			   PM_QOS_CPU_DMA_LATENCY, PM_QOS_DEFAULT_VALUE);

	mutex_init(&dev_priv->av_mutex);
	mutex_init(&dev_priv->wm.wm_mutex);
	mutex_init(&dev_priv->pps_mutex);
	mutex_init(&dev_priv->hdcp_comp_mutex);

	i915_memcpy_init_early(dev_priv);
	intel_runtime_pm_init_early(&dev_priv->runtime_pm);

	ret = i915_workqueues_init(dev_priv);
	if (ret < 0)
		return ret;

	ret = vlv_alloc_s0ix_state(dev_priv);
	if (ret < 0)
		goto err_workqueues;

	intel_wopcm_init_early(&dev_priv->wopcm);

	intel_gt_init_early(&dev_priv->gt, dev_priv);

	ret = i915_gem_init_early(dev_priv);
	if (ret < 0)
		goto err_gt;

	/* This must be called before any calls to HAS_PCH_* */
	intel_detect_pch(dev_priv);

	intel_pm_setup(dev_priv);
	intel_init_dpio(dev_priv);
	ret = intel_power_domains_init(dev_priv);
	if (ret < 0)
		goto err_gem;
	intel_irq_init(dev_priv);
	intel_init_display_hooks(dev_priv);
	intel_init_clock_gating_hooks(dev_priv);
	intel_init_audio_hooks(dev_priv);
	intel_display_crc_init(dev_priv);

	intel_detect_preproduction_hw(dev_priv);

	return 0;

err_gem:
	i915_gem_cleanup_early(dev_priv);
err_gt:
	intel_gt_driver_late_release(&dev_priv->gt);
	vlv_free_s0ix_state(dev_priv);
err_workqueues:
	i915_workqueues_cleanup(dev_priv);
	return ret;
}