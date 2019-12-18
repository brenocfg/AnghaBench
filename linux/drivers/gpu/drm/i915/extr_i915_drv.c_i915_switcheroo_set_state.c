#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {void* switch_power_state; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ pm_message_t ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;

/* Variables and functions */
 void* DRM_SWITCH_POWER_CHANGING ; 
 void* DRM_SWITCH_POWER_OFF ; 
 void* DRM_SWITCH_POWER_ON ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PM_EVENT_SUSPEND ; 
 int VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i915_resume_switcheroo (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_suspend_switcheroo (struct drm_i915_private*,TYPE_2__) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* pdev_to_i915 (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void i915_switcheroo_set_state(struct pci_dev *pdev, enum vga_switcheroo_state state)
{
	struct drm_i915_private *i915 = pdev_to_i915(pdev);
	pm_message_t pmm = { .event = PM_EVENT_SUSPEND };

	if (!i915) {
		dev_err(&pdev->dev, "DRM not initialized, aborting switch.\n");
		return;
	}

	if (state == VGA_SWITCHEROO_ON) {
		pr_info("switched on\n");
		i915->drm.switch_power_state = DRM_SWITCH_POWER_CHANGING;
		/* i915 resume handler doesn't set to D0 */
		pci_set_power_state(pdev, PCI_D0);
		i915_resume_switcheroo(i915);
		i915->drm.switch_power_state = DRM_SWITCH_POWER_ON;
	} else {
		pr_info("switched off\n");
		i915->drm.switch_power_state = DRM_SWITCH_POWER_CHANGING;
		i915_suspend_switcheroo(i915, pmm);
		i915->drm.switch_power_state = DRM_SWITCH_POWER_OFF;
	}
}