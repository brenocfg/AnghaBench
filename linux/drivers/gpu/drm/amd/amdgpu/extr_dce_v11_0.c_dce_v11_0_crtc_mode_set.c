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
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct amdgpu_encoder {int /*<<< orphan*/  encoder_id; } ;
struct amdgpu_device {scalar_t__ asic_type; } ;
struct amdgpu_crtc {struct drm_display_mode hw_mode; int /*<<< orphan*/  ss; int /*<<< orphan*/  ss_enabled; int /*<<< orphan*/  bpc; int /*<<< orphan*/  pll_id; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  encoder; int /*<<< orphan*/  adjusted_clock; } ;

/* Variables and functions */
 scalar_t__ CHIP_POLARIS10 ; 
 scalar_t__ CHIP_POLARIS11 ; 
 scalar_t__ CHIP_POLARIS12 ; 
 scalar_t__ CHIP_VEGAM ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_overscan_setup (struct drm_crtc*,struct drm_display_mode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_program_pll (struct drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_scaler_setup (struct drm_crtc*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_set_dtd_timing (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_set_pll (struct drm_crtc*,struct drm_display_mode*) ; 
 int amdgpu_atombios_encoder_get_encoder_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v11_0_crtc_do_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v11_0_cursor_reset (struct drm_crtc*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dce_v11_0_crtc_mode_set(struct drm_crtc *crtc,
				  struct drm_display_mode *mode,
				  struct drm_display_mode *adjusted_mode,
				  int x, int y, struct drm_framebuffer *old_fb)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;

	if (!amdgpu_crtc->adjusted_clock)
		return -EINVAL;

	if ((adev->asic_type == CHIP_POLARIS10) ||
	    (adev->asic_type == CHIP_POLARIS11) ||
	    (adev->asic_type == CHIP_POLARIS12) ||
	    (adev->asic_type == CHIP_VEGAM)) {
		struct amdgpu_encoder *amdgpu_encoder =
			to_amdgpu_encoder(amdgpu_crtc->encoder);
		int encoder_mode =
			amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder);

		/* SetPixelClock calculates the plls and ss values now */
		amdgpu_atombios_crtc_program_pll(crtc, amdgpu_crtc->crtc_id,
						 amdgpu_crtc->pll_id,
						 encoder_mode, amdgpu_encoder->encoder_id,
						 adjusted_mode->clock, 0, 0, 0, 0,
						 amdgpu_crtc->bpc, amdgpu_crtc->ss_enabled, &amdgpu_crtc->ss);
	} else {
		amdgpu_atombios_crtc_set_pll(crtc, adjusted_mode);
	}
	amdgpu_atombios_crtc_set_dtd_timing(crtc, adjusted_mode);
	dce_v11_0_crtc_do_set_base(crtc, old_fb, x, y, 0);
	amdgpu_atombios_crtc_overscan_setup(crtc, mode, adjusted_mode);
	amdgpu_atombios_crtc_scaler_setup(crtc);
	dce_v11_0_cursor_reset(crtc);
	/* update the hw version fpr dpm */
	amdgpu_crtc->hw_mode = *adjusted_mode;

	return 0;
}