#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_work; } ;
struct drm_i915_private {int /*<<< orphan*/  modeset_wq; TYPE_1__ atomic_helper; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_fbc_cleanup_cfb (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_global_disable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbdev_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gmbus_teardown (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hdcp_component_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  intel_irq_uninstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_overlay_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_unregister_dsm_handler () ; 
 int /*<<< orphan*/  llist_empty (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_modeset_driver_remove(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	flush_workqueue(dev_priv->modeset_wq);

	flush_work(&dev_priv->atomic_helper.free_work);
	WARN_ON(!llist_empty(&dev_priv->atomic_helper.free_list));

	/*
	 * Interrupts and polling as the first thing to avoid creating havoc.
	 * Too much stuff here (turning of connectors, ...) would
	 * experience fancy races otherwise.
	 */
	intel_irq_uninstall(dev_priv);

	/*
	 * Due to the hpd irq storm handling the hotplug work can re-arm the
	 * poll handlers. Hence disable polling after hpd handling is shut down.
	 */
	intel_hpd_poll_fini(dev);

	/* poll work can call into fbdev, hence clean that up afterwards */
	intel_fbdev_fini(dev_priv);

	intel_unregister_dsm_handler();

	intel_fbc_global_disable(dev_priv);

	/* flush any delayed tasks or pending work */
	flush_scheduled_work();

	intel_hdcp_component_fini(dev_priv);

	drm_mode_config_cleanup(dev);

	intel_overlay_cleanup(dev_priv);

	intel_gmbus_teardown(dev_priv);

	destroy_workqueue(dev_priv->modeset_wq);

	intel_fbc_cleanup_cfb(dev_priv);
}