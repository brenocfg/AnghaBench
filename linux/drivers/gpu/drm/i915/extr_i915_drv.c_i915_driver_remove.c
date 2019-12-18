#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_7__ {TYPE_1__ hangcheck; } ;
struct TYPE_6__ {struct pci_dev* pdev; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; TYPE_3__ gt; TYPE_2__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_driver_hw_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_driver_unregister (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_driver_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_reset_error_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_bios_driver_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_ucode_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_gvt_driver_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_modeset_driver_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_power_domains_driver_remove (struct drm_i915_private*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  vga_client_register (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (struct pci_dev*) ; 

void i915_driver_remove(struct drm_i915_private *i915)
{
	struct pci_dev *pdev = i915->drm.pdev;

	disable_rpm_wakeref_asserts(&i915->runtime_pm);

	i915_driver_unregister(i915);

	/*
	 * After unregistering the device to prevent any new users, cancel
	 * all in-flight requests so that we can quickly unbind the active
	 * resources.
	 */
	intel_gt_set_wedged(&i915->gt);

	/* Flush any external code that still may be under the RCU lock */
	synchronize_rcu();

	i915_gem_suspend(i915);

	drm_atomic_helper_shutdown(&i915->drm);

	intel_gvt_driver_remove(i915);

	intel_modeset_driver_remove(&i915->drm);

	intel_bios_driver_remove(i915);

	vga_switcheroo_unregister_client(pdev);
	vga_client_register(pdev, NULL, NULL, NULL);

	intel_csr_ucode_fini(i915);

	/* Free error state after interrupts are fully disabled. */
	cancel_delayed_work_sync(&i915->gt.hangcheck.work);
	i915_reset_error_state(i915);

	i915_gem_driver_remove(i915);

	intel_power_domains_driver_remove(i915);

	i915_driver_hw_remove(i915);

	enable_rpm_wakeref_asserts(&i915->runtime_pm);
}