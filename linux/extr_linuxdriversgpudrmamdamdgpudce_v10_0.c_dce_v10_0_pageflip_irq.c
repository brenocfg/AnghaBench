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
struct amdgpu_iv_entry {int src_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_flip_work {int /*<<< orphan*/  unpin_work; scalar_t__ event; } ;
struct TYPE_3__ {unsigned int num_crtc; struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_2__* ddev; TYPE_1__ mode_info; } ;
struct amdgpu_crtc {scalar_t__ pflip_status; int /*<<< orphan*/  base; struct amdgpu_flip_work* pflip_works; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FLIP_NONE ; 
 scalar_t__ AMDGPU_FLIP_SUBMITTED ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_CLEAR_MASK ; 
 int GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_OCCURRED_MASK ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* crtc_offsets ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (int /*<<< orphan*/ *) ; 
 scalar_t__ mmGRPH_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dce_v10_0_pageflip_irq(struct amdgpu_device *adev,
				  struct amdgpu_irq_src *source,
				  struct amdgpu_iv_entry *entry)
{
	unsigned long flags;
	unsigned crtc_id;
	struct amdgpu_crtc *amdgpu_crtc;
	struct amdgpu_flip_work *works;

	crtc_id = (entry->src_id - 8) >> 1;
	amdgpu_crtc = adev->mode_info.crtcs[crtc_id];

	if (crtc_id >= adev->mode_info.num_crtc) {
		DRM_ERROR("invalid pageflip crtc %d\n", crtc_id);
		return -EINVAL;
	}

	if (RREG32(mmGRPH_INTERRUPT_STATUS + crtc_offsets[crtc_id]) &
	    GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_OCCURRED_MASK)
		WREG32(mmGRPH_INTERRUPT_STATUS + crtc_offsets[crtc_id],
		       GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_CLEAR_MASK);

	/* IRQ could occur when in initial stage */
	if (amdgpu_crtc == NULL)
		return 0;

	spin_lock_irqsave(&adev->ddev->event_lock, flags);
	works = amdgpu_crtc->pflip_works;
	if (amdgpu_crtc->pflip_status != AMDGPU_FLIP_SUBMITTED) {
		DRM_DEBUG_DRIVER("amdgpu_crtc->pflip_status = %d != "
						 "AMDGPU_FLIP_SUBMITTED(%d)\n",
						 amdgpu_crtc->pflip_status,
						 AMDGPU_FLIP_SUBMITTED);
		spin_unlock_irqrestore(&adev->ddev->event_lock, flags);
		return 0;
	}

	/* page flip completed. clean up */
	amdgpu_crtc->pflip_status = AMDGPU_FLIP_NONE;
	amdgpu_crtc->pflip_works = NULL;

	/* wakeup usersapce */
	if (works->event)
		drm_crtc_send_vblank_event(&amdgpu_crtc->base, works->event);

	spin_unlock_irqrestore(&adev->ddev->event_lock, flags);

	drm_crtc_vblank_put(&amdgpu_crtc->base);
	schedule_work(&works->unpin_work);

	return 0;
}