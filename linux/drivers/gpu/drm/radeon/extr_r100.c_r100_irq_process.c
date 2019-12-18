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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pflip; int /*<<< orphan*/  vblank_queue; scalar_t__* crtc_vblank_int; } ;
struct TYPE_3__ {int vblank_sync; } ;
struct radeon_device {int family; scalar_t__ msi_enabled; int /*<<< orphan*/  hotplug_work; TYPE_2__ irq; TYPE_1__ pm; int /*<<< orphan*/  ddev; scalar_t__ shutdown; } ;

/* Variables and functions */
#define  CHIP_RS400 129 
#define  CHIP_RS480 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  RADEON_AIC_CNTL ; 
 int RADEON_CRTC2_VBLANK_STAT ; 
 int RADEON_CRTC_VBLANK_STAT ; 
 int RADEON_FP2_DETECT_STAT ; 
 int RADEON_FP_DETECT_STAT ; 
 int /*<<< orphan*/  RADEON_MSI_REARM_EN ; 
 int /*<<< orphan*/  RADEON_RING_TYPE_GFX_INDEX ; 
 int RADEON_SW_INT_TEST ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RS400_MSI_REARM ; 
 int RV370_MSI_REARM_EN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_handle_vblank (int /*<<< orphan*/ ,int) ; 
 int r100_irq_ack (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_crtc_handle_vblank (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_fence_process (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int r100_irq_process(struct radeon_device *rdev)
{
	uint32_t status, msi_rearm;
	bool queue_hotplug = false;

	status = r100_irq_ack(rdev);
	if (!status) {
		return IRQ_NONE;
	}
	if (rdev->shutdown) {
		return IRQ_NONE;
	}
	while (status) {
		/* SW interrupt */
		if (status & RADEON_SW_INT_TEST) {
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
		}
		/* Vertical blank interrupts */
		if (status & RADEON_CRTC_VBLANK_STAT) {
			if (rdev->irq.crtc_vblank_int[0]) {
				drm_handle_vblank(rdev->ddev, 0);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			}
			if (atomic_read(&rdev->irq.pflip[0]))
				radeon_crtc_handle_vblank(rdev, 0);
		}
		if (status & RADEON_CRTC2_VBLANK_STAT) {
			if (rdev->irq.crtc_vblank_int[1]) {
				drm_handle_vblank(rdev->ddev, 1);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			}
			if (atomic_read(&rdev->irq.pflip[1]))
				radeon_crtc_handle_vblank(rdev, 1);
		}
		if (status & RADEON_FP_DETECT_STAT) {
			queue_hotplug = true;
			DRM_DEBUG("HPD1\n");
		}
		if (status & RADEON_FP2_DETECT_STAT) {
			queue_hotplug = true;
			DRM_DEBUG("HPD2\n");
		}
		status = r100_irq_ack(rdev);
	}
	if (queue_hotplug)
		schedule_delayed_work(&rdev->hotplug_work, 0);
	if (rdev->msi_enabled) {
		switch (rdev->family) {
		case CHIP_RS400:
		case CHIP_RS480:
			msi_rearm = RREG32(RADEON_AIC_CNTL) & ~RS400_MSI_REARM;
			WREG32(RADEON_AIC_CNTL, msi_rearm);
			WREG32(RADEON_AIC_CNTL, msi_rearm | RS400_MSI_REARM);
			break;
		default:
			WREG32(RADEON_MSI_REARM_EN, RV370_MSI_REARM_EN);
			break;
		}
	}
	return IRQ_HANDLED;
}