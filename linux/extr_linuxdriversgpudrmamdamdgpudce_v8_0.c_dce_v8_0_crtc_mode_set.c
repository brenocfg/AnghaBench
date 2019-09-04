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
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct amdgpu_crtc {struct drm_display_mode hw_mode; int /*<<< orphan*/  adjusted_clock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_overscan_setup (struct drm_crtc*,struct drm_display_mode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_scaler_setup (struct drm_crtc*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_set_dtd_timing (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_set_pll (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dce_v8_0_crtc_do_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v8_0_cursor_reset (struct drm_crtc*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int dce_v8_0_crtc_mode_set(struct drm_crtc *crtc,
				  struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode,
				  int x, int y, struct drm_framebuffer *old_fb)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	if (!amdgpu_crtc->adjusted_clock)
		return -EINVAL;

	amdgpu_atombios_crtc_set_pll(crtc, adjusted_mode);
	amdgpu_atombios_crtc_set_dtd_timing(crtc, adjusted_mode);
	dce_v8_0_crtc_do_set_base(crtc, old_fb, x, y, 0);
	amdgpu_atombios_crtc_overscan_setup(crtc, mode, adjusted_mode);
	amdgpu_atombios_crtc_scaler_setup(crtc);
	dce_v8_0_cursor_reset(crtc);
	/* update the hw version fpr dpm */
	amdgpu_crtc->hw_mode = *adjusted_mode;

	return 0;
}