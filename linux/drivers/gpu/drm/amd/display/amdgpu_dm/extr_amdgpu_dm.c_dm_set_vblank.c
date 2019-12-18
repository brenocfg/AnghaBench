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
struct drm_crtc {int /*<<< orphan*/  state; TYPE_2__* dev; } ;
struct dm_crtc_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dc; } ;
struct amdgpu_device {TYPE_1__ dm; } ;
struct amdgpu_crtc {int otg_inst; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;
struct TYPE_4__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int EBUSY ; 
 int IRQ_TYPE_VBLANK ; 
 scalar_t__ amdgpu_dm_vrr_active (struct dm_crtc_state*) ; 
 scalar_t__ dc_interrupt_set (int /*<<< orphan*/ ,int,int) ; 
 int dm_set_vupdate_irq (struct drm_crtc*,int) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 struct dm_crtc_state* to_dm_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dm_set_vblank(struct drm_crtc *crtc, bool enable)
{
	enum dc_irq_source irq_source;
	struct amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);
	struct amdgpu_device *adev = crtc->dev->dev_private;
	struct dm_crtc_state *acrtc_state = to_dm_crtc_state(crtc->state);
	int rc = 0;

	if (enable) {
		/* vblank irq on -> Only need vupdate irq in vrr mode */
		if (amdgpu_dm_vrr_active(acrtc_state))
			rc = dm_set_vupdate_irq(crtc, true);
	} else {
		/* vblank irq off -> vupdate irq off */
		rc = dm_set_vupdate_irq(crtc, false);
	}

	if (rc)
		return rc;

	irq_source = IRQ_TYPE_VBLANK + acrtc->otg_inst;
	return dc_interrupt_set(adev->dm.dc, irq_source, enable) ? 0 : -EBUSY;
}