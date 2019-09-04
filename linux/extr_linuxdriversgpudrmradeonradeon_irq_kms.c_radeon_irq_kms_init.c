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
struct TYPE_6__ {int installed; int /*<<< orphan*/  lock; } ;
struct radeon_device {int msi_enabled; int /*<<< orphan*/  hotplug_work; TYPE_2__ irq; TYPE_3__* ddev; int /*<<< orphan*/  audio_work; int /*<<< orphan*/  dp_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  num_crtc; } ;
struct TYPE_7__ {int vblank_disable_immediate; TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int drm_irq_install (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int drm_vblank_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int pci_enable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_audio_update_hdmi ; 
 int /*<<< orphan*/  radeon_dp_work_func ; 
 int /*<<< orphan*/  radeon_hotplug_work_func ; 
 scalar_t__ radeon_msi_ok (struct radeon_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int radeon_irq_kms_init(struct radeon_device *rdev)
{
	int r = 0;

	spin_lock_init(&rdev->irq.lock);

	/* Disable vblank irqs aggressively for power-saving */
	rdev->ddev->vblank_disable_immediate = true;

	r = drm_vblank_init(rdev->ddev, rdev->num_crtc);
	if (r) {
		return r;
	}

	/* enable msi */
	rdev->msi_enabled = 0;

	if (radeon_msi_ok(rdev)) {
		int ret = pci_enable_msi(rdev->pdev);
		if (!ret) {
			rdev->msi_enabled = 1;
			dev_info(rdev->dev, "radeon: using MSI.\n");
		}
	}

	INIT_DELAYED_WORK(&rdev->hotplug_work, radeon_hotplug_work_func);
	INIT_WORK(&rdev->dp_work, radeon_dp_work_func);
	INIT_WORK(&rdev->audio_work, r600_audio_update_hdmi);

	rdev->irq.installed = true;
	r = drm_irq_install(rdev->ddev, rdev->ddev->pdev->irq);
	if (r) {
		rdev->irq.installed = false;
		flush_delayed_work(&rdev->hotplug_work);
		return r;
	}

	DRM_INFO("radeon: irq initialized.\n");
	return 0;
}