#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int dummy; } ;
struct drm_device {void* switch_power_state; } ;
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;

/* Variables and functions */
 void* DRM_SWITCH_POWER_CHANGING ; 
 void* DRM_SWITCH_POWER_OFF ; 
 void* DRM_SWITCH_POWER_ON ; 
 int VGA_SWITCHEROO_OFF ; 
 int VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ radeon_is_px (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_resume_kms (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  radeon_suspend_kms (struct drm_device*,int,int,int) ; 

__attribute__((used)) static void radeon_switcheroo_set_state(struct pci_dev *pdev, enum vga_switcheroo_state state)
{
	struct drm_device *dev = pci_get_drvdata(pdev);

	if (radeon_is_px(dev) && state == VGA_SWITCHEROO_OFF)
		return;

	if (state == VGA_SWITCHEROO_ON) {
		pr_info("radeon: switched on\n");
		/* don't suspend or resume card normally */
		dev->switch_power_state = DRM_SWITCH_POWER_CHANGING;

		radeon_resume_kms(dev, true, true);

		dev->switch_power_state = DRM_SWITCH_POWER_ON;
		drm_kms_helper_poll_enable(dev);
	} else {
		pr_info("radeon: switched off\n");
		drm_kms_helper_poll_disable(dev);
		dev->switch_power_state = DRM_SWITCH_POWER_CHANGING;
		radeon_suspend_kms(dev, true, true, false);
		dev->switch_power_state = DRM_SWITCH_POWER_OFF;
	}
}