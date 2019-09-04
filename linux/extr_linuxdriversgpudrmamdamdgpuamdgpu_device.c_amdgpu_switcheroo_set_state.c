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
 scalar_t__ amdgpu_device_is_px (struct drm_device*) ; 
 int /*<<< orphan*/  amdgpu_device_resume (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  amdgpu_device_suspend (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void amdgpu_switcheroo_set_state(struct pci_dev *pdev, enum vga_switcheroo_state state)
{
	struct drm_device *dev = pci_get_drvdata(pdev);

	if (amdgpu_device_is_px(dev) && state == VGA_SWITCHEROO_OFF)
		return;

	if (state == VGA_SWITCHEROO_ON) {
		pr_info("amdgpu: switched on\n");
		/* don't suspend or resume card normally */
		dev->switch_power_state = DRM_SWITCH_POWER_CHANGING;

		amdgpu_device_resume(dev, true, true);

		dev->switch_power_state = DRM_SWITCH_POWER_ON;
		drm_kms_helper_poll_enable(dev);
	} else {
		pr_info("amdgpu: switched off\n");
		drm_kms_helper_poll_disable(dev);
		dev->switch_power_state = DRM_SWITCH_POWER_CHANGING;
		amdgpu_device_suspend(dev, true, true);
		dev->switch_power_state = DRM_SWITCH_POWER_OFF;
	}
}