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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct amdgpu_device {int /*<<< orphan*/  crtc_irq; } ;
struct amdgpu_crtc {int enabled; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 unsigned int amdgpu_display_crtc_idx_to_irq_type (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_irq_update (struct amdgpu_device*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_virtual_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	unsigned type;

	if (amdgpu_sriov_vf(adev))
		return;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		amdgpu_crtc->enabled = true;
		/* Make sure VBLANK interrupts are still enabled */
		type = amdgpu_display_crtc_idx_to_irq_type(adev,
						amdgpu_crtc->crtc_id);
		amdgpu_irq_update(adev, &adev->crtc_irq, type);
		drm_crtc_vblank_on(crtc);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		drm_crtc_vblank_off(crtc);
		amdgpu_crtc->enabled = false;
		break;
	}
}