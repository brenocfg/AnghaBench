#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int msi_enabled; int installed; int /*<<< orphan*/  ih2_work; int /*<<< orphan*/  ih1_work; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_crtc; } ;
struct amdgpu_device {TYPE_4__* ddev; int /*<<< orphan*/  hotplug_work; TYPE_3__ irq; TYPE_1__ mode_info; int /*<<< orphan*/  enable_virtual_display; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;
struct TYPE_9__ {int vblank_disable_immediate; int max_vblank_count; TYPE_2__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_hotplug_work_func ; 
 int /*<<< orphan*/  amdgpu_irq_handle_ih1 ; 
 int /*<<< orphan*/  amdgpu_irq_handle_ih2 ; 
 scalar_t__ amdgpu_msi_ok (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int drm_irq_install (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int drm_vblank_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int pci_enable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int amdgpu_irq_init(struct amdgpu_device *adev)
{
	int r = 0;

	spin_lock_init(&adev->irq.lock);

	/* Enable MSI if not disabled by module parameter */
	adev->irq.msi_enabled = false;

	if (amdgpu_msi_ok(adev)) {
		int ret = pci_enable_msi(adev->pdev);
		if (!ret) {
			adev->irq.msi_enabled = true;
			dev_dbg(adev->dev, "amdgpu: using MSI.\n");
		}
	}

	if (!amdgpu_device_has_dc_support(adev)) {
		if (!adev->enable_virtual_display)
			/* Disable vblank IRQs aggressively for power-saving */
			/* XXX: can this be enabled for DC? */
			adev->ddev->vblank_disable_immediate = true;

		r = drm_vblank_init(adev->ddev, adev->mode_info.num_crtc);
		if (r)
			return r;

		/* Pre-DCE11 */
		INIT_WORK(&adev->hotplug_work,
				amdgpu_hotplug_work_func);
	}

	INIT_WORK(&adev->irq.ih1_work, amdgpu_irq_handle_ih1);
	INIT_WORK(&adev->irq.ih2_work, amdgpu_irq_handle_ih2);

	adev->irq.installed = true;
	r = drm_irq_install(adev->ddev, adev->ddev->pdev->irq);
	if (r) {
		adev->irq.installed = false;
		if (!amdgpu_device_has_dc_support(adev))
			flush_work(&adev->hotplug_work);
		return r;
	}
	adev->ddev->max_vblank_count = 0x00ffffff;

	DRM_DEBUG("amdgpu: irq initialized.\n");
	return 0;
}