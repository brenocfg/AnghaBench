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
struct amdgpu_device {int /*<<< orphan*/  pageflip_irq; } ;
struct amdgpu_crtc {int /*<<< orphan*/  base; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 int amdgpu_display_crtc_idx_to_irq_type (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_irq_get (struct amdgpu_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void manage_dm_interrupts(struct amdgpu_device *adev,
				 struct amdgpu_crtc *acrtc,
				 bool enable)
{
	/*
	 * this is not correct translation but will work as soon as VBLANK
	 * constant is the same as PFLIP
	 */
	int irq_type =
		amdgpu_display_crtc_idx_to_irq_type(
			adev,
			acrtc->crtc_id);

	if (enable) {
		drm_crtc_vblank_on(&acrtc->base);
		amdgpu_irq_get(
			adev,
			&adev->pageflip_irq,
			irq_type);
	} else {

		amdgpu_irq_put(
			adev,
			&adev->pageflip_irq,
			irq_type);
		drm_crtc_vblank_off(&acrtc->base);
	}
}