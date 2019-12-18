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
struct amdgpu_device {int /*<<< orphan*/  pageflip_irq; int /*<<< orphan*/  crtc_irq; } ;
struct amdgpu_crtc {int enabled; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  amdgpu_atombios_crtc_blank (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_enable (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 unsigned int amdgpu_display_crtc_idx_to_irq_type (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_irq_update (struct amdgpu_device*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  amdgpu_pm_compute_clocks (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  dce_v10_0_vga_enable (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_v10_0_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	unsigned type;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		amdgpu_crtc->enabled = true;
		amdgpu_atombios_crtc_enable(crtc, ATOM_ENABLE);
		dce_v10_0_vga_enable(crtc, true);
		amdgpu_atombios_crtc_blank(crtc, ATOM_DISABLE);
		dce_v10_0_vga_enable(crtc, false);
		/* Make sure VBLANK and PFLIP interrupts are still enabled */
		type = amdgpu_display_crtc_idx_to_irq_type(adev,
						amdgpu_crtc->crtc_id);
		amdgpu_irq_update(adev, &adev->crtc_irq, type);
		amdgpu_irq_update(adev, &adev->pageflip_irq, type);
		drm_crtc_vblank_on(crtc);
		dce_v10_0_crtc_load_lut(crtc);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		drm_crtc_vblank_off(crtc);
		if (amdgpu_crtc->enabled) {
			dce_v10_0_vga_enable(crtc, true);
			amdgpu_atombios_crtc_blank(crtc, ATOM_ENABLE);
			dce_v10_0_vga_enable(crtc, false);
		}
		amdgpu_atombios_crtc_enable(crtc, ATOM_DISABLE);
		amdgpu_crtc->enabled = false;
		break;
	}
	/* adjust pm to dpms */
	amdgpu_pm_compute_clocks(adev);
}