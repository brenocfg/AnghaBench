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
typedef  int /*<<< orphan*/  u16 ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {int gamma_size; int /*<<< orphan*/ * gamma_store; struct drm_device* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 int DEGAMMA_CONTROL__CURSOR_DEGAMMA_MODE__SHIFT ; 
 int DEGAMMA_CONTROL__GRPH_DEGAMMA_MODE__SHIFT ; 
 int DEGAMMA_CONTROL__OVL_DEGAMMA_MODE__SHIFT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int GAMUT_REMAP_CONTROL__GRPH_GAMUT_REMAP_MODE__SHIFT ; 
 int GAMUT_REMAP_CONTROL__OVL_GAMUT_REMAP_MODE__SHIFT ; 
 int ICON_DEGAMMA_MODE (int /*<<< orphan*/ ) ; 
 int INPUT_CSC_CONTROL__INPUT_CSC_GRPH_MODE__SHIFT ; 
 int INPUT_CSC_CONTROL__INPUT_CSC_OVL_MODE__SHIFT ; 
 int INPUT_GAMMA_CONTROL__GRPH_INPUT_GAMMA_MODE__SHIFT ; 
 int INPUT_GAMMA_CONTROL__OVL_INPUT_GAMMA_MODE__SHIFT ; 
 int OUTPUT_CSC_CONTROL__OUTPUT_CSC_GRPH_MODE__SHIFT ; 
 int OUTPUT_CSC_CONTROL__OUTPUT_CSC_OVL_MODE__SHIFT ; 
 int PRESCALE_GRPH_CONTROL__GRPH_PRESCALE_BYPASS_MASK ; 
 int PRESCALE_OVL_CONTROL__OVL_PRESCALE_BYPASS_MASK ; 
 int REGAMMA_CONTROL__GRPH_REGAMMA_MODE__SHIFT ; 
 int REGAMMA_CONTROL__OVL_REGAMMA_MODE__SHIFT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmDC_LUT_30_COLOR ; 
 scalar_t__ mmDC_LUT_BLACK_OFFSET_BLUE ; 
 scalar_t__ mmDC_LUT_BLACK_OFFSET_GREEN ; 
 scalar_t__ mmDC_LUT_BLACK_OFFSET_RED ; 
 scalar_t__ mmDC_LUT_CONTROL ; 
 scalar_t__ mmDC_LUT_RW_INDEX ; 
 scalar_t__ mmDC_LUT_RW_MODE ; 
 scalar_t__ mmDC_LUT_WHITE_OFFSET_BLUE ; 
 scalar_t__ mmDC_LUT_WHITE_OFFSET_GREEN ; 
 scalar_t__ mmDC_LUT_WHITE_OFFSET_RED ; 
 scalar_t__ mmDC_LUT_WRITE_EN_MASK ; 
 scalar_t__ mmDEGAMMA_CONTROL ; 
 scalar_t__ mmGAMUT_REMAP_CONTROL ; 
 scalar_t__ mmINPUT_CSC_CONTROL ; 
 scalar_t__ mmINPUT_GAMMA_CONTROL ; 
 scalar_t__ mmOUTPUT_CSC_CONTROL ; 
 scalar_t__ mmPRESCALE_GRPH_CONTROL ; 
 scalar_t__ mmPRESCALE_OVL_CONTROL ; 
 scalar_t__ mmREGAMMA_CONTROL ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_v6_0_crtc_load_lut(struct drm_crtc *crtc)
{

	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	u16 *r, *g, *b;
	int i;

	DRM_DEBUG_KMS("%d\n", amdgpu_crtc->crtc_id);

	WREG32(mmINPUT_CSC_CONTROL + amdgpu_crtc->crtc_offset,
	       ((0 << INPUT_CSC_CONTROL__INPUT_CSC_GRPH_MODE__SHIFT) |
		(0 << INPUT_CSC_CONTROL__INPUT_CSC_OVL_MODE__SHIFT)));
	WREG32(mmPRESCALE_GRPH_CONTROL + amdgpu_crtc->crtc_offset,
	       PRESCALE_GRPH_CONTROL__GRPH_PRESCALE_BYPASS_MASK);
	WREG32(mmPRESCALE_OVL_CONTROL + amdgpu_crtc->crtc_offset,
	       PRESCALE_OVL_CONTROL__OVL_PRESCALE_BYPASS_MASK);
	WREG32(mmINPUT_GAMMA_CONTROL + amdgpu_crtc->crtc_offset,
	       ((0 << INPUT_GAMMA_CONTROL__GRPH_INPUT_GAMMA_MODE__SHIFT) |
		(0 << INPUT_GAMMA_CONTROL__OVL_INPUT_GAMMA_MODE__SHIFT)));

	WREG32(mmDC_LUT_CONTROL + amdgpu_crtc->crtc_offset, 0);

	WREG32(mmDC_LUT_BLACK_OFFSET_BLUE + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmDC_LUT_BLACK_OFFSET_GREEN + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmDC_LUT_BLACK_OFFSET_RED + amdgpu_crtc->crtc_offset, 0);

	WREG32(mmDC_LUT_WHITE_OFFSET_BLUE + amdgpu_crtc->crtc_offset, 0xffff);
	WREG32(mmDC_LUT_WHITE_OFFSET_GREEN + amdgpu_crtc->crtc_offset, 0xffff);
	WREG32(mmDC_LUT_WHITE_OFFSET_RED + amdgpu_crtc->crtc_offset, 0xffff);

	WREG32(mmDC_LUT_RW_MODE + amdgpu_crtc->crtc_offset, 0);
	WREG32(mmDC_LUT_WRITE_EN_MASK + amdgpu_crtc->crtc_offset, 0x00000007);

	WREG32(mmDC_LUT_RW_INDEX + amdgpu_crtc->crtc_offset, 0);
	r = crtc->gamma_store;
	g = r + crtc->gamma_size;
	b = g + crtc->gamma_size;
	for (i = 0; i < 256; i++) {
		WREG32(mmDC_LUT_30_COLOR + amdgpu_crtc->crtc_offset,
		       ((*r++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	}

	WREG32(mmDEGAMMA_CONTROL + amdgpu_crtc->crtc_offset,
	       ((0 << DEGAMMA_CONTROL__GRPH_DEGAMMA_MODE__SHIFT) |
		(0 << DEGAMMA_CONTROL__OVL_DEGAMMA_MODE__SHIFT) |
		ICON_DEGAMMA_MODE(0) |
		(0 << DEGAMMA_CONTROL__CURSOR_DEGAMMA_MODE__SHIFT)));
	WREG32(mmGAMUT_REMAP_CONTROL + amdgpu_crtc->crtc_offset,
	       ((0 << GAMUT_REMAP_CONTROL__GRPH_GAMUT_REMAP_MODE__SHIFT) |
		(0 << GAMUT_REMAP_CONTROL__OVL_GAMUT_REMAP_MODE__SHIFT)));
	WREG32(mmREGAMMA_CONTROL + amdgpu_crtc->crtc_offset,
	       ((0 << REGAMMA_CONTROL__GRPH_REGAMMA_MODE__SHIFT) |
		(0 << REGAMMA_CONTROL__OVL_REGAMMA_MODE__SHIFT)));
	WREG32(mmOUTPUT_CSC_CONTROL + amdgpu_crtc->crtc_offset,
	       ((0 << OUTPUT_CSC_CONTROL__OUTPUT_CSC_GRPH_MODE__SHIFT) |
		(0 << OUTPUT_CSC_CONTROL__OUTPUT_CSC_OVL_MODE__SHIFT)));
	/* XXX match this to the depth of the crtc fmt block, move to modeset? */
	WREG32(0x1a50 + amdgpu_crtc->crtc_offset, 0);


}