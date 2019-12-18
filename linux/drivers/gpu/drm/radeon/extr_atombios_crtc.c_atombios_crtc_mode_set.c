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
struct radeon_encoder {int active_device; } ;
struct radeon_device {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct radeon_crtc {scalar_t__ crtc_id; struct drm_display_mode hw_mode; int /*<<< orphan*/  adjusted_clock; int /*<<< orphan*/  encoder; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  atombios_crtc_set_base (struct drm_crtc*,int,int,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  atombios_crtc_set_pll (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  atombios_crtc_set_timing (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  atombios_overscan_setup (struct drm_crtc*,struct drm_display_mode*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  atombios_scaler_setup (struct drm_crtc*) ; 
 int /*<<< orphan*/  atombios_set_crtc_dtd_timing (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_cursor_reset (struct drm_crtc*) ; 
 int /*<<< orphan*/  radeon_legacy_atom_fixup (struct drm_crtc*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_encoder* to_radeon_encoder (int /*<<< orphan*/ ) ; 

int atombios_crtc_mode_set(struct drm_crtc *crtc,
			   struct drm_display_mode *mode,
			   struct drm_display_mode *adjusted_mode,
			   int x, int y, struct drm_framebuffer *old_fb)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	bool is_tvcv = false;

	if (radeon_encoder->active_device &
	    (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))
		is_tvcv = true;

	if (!radeon_crtc->adjusted_clock)
		return -EINVAL;

	atombios_crtc_set_pll(crtc, adjusted_mode);

	if (ASIC_IS_DCE4(rdev))
		atombios_set_crtc_dtd_timing(crtc, adjusted_mode);
	else if (ASIC_IS_AVIVO(rdev)) {
		if (is_tvcv)
			atombios_crtc_set_timing(crtc, adjusted_mode);
		else
			atombios_set_crtc_dtd_timing(crtc, adjusted_mode);
	} else {
		atombios_crtc_set_timing(crtc, adjusted_mode);
		if (radeon_crtc->crtc_id == 0)
			atombios_set_crtc_dtd_timing(crtc, adjusted_mode);
		radeon_legacy_atom_fixup(crtc);
	}
	atombios_crtc_set_base(crtc, x, y, old_fb);
	atombios_overscan_setup(crtc, mode, adjusted_mode);
	atombios_scaler_setup(crtc);
	radeon_cursor_reset(crtc);
	/* update the hw version fpr dpm */
	radeon_crtc->hw_mode = *adjusted_mode;

	return 0;
}