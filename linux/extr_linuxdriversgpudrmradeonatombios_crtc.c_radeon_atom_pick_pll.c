#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_encoder_atom_dig {int linkb; } ;
struct radeon_encoder {scalar_t__ encoder_id; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_2__ {scalar_t__ dp_extclk; } ;
struct radeon_device {scalar_t__ family; TYPE_1__ clock; } ;
struct radeon_crtc {int crtc_id; int /*<<< orphan*/  encoder; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE41 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE61 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 int ATOM_DCPLL ; 
 int ATOM_PPLL0 ; 
 int ATOM_PPLL1 ; 
 int ATOM_PPLL2 ; 
 int ATOM_PPLL_INVALID ; 
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ ENCODER_MODE_IS_DP (int /*<<< orphan*/ ) ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_UNIPHY ; 
 int /*<<< orphan*/  atombios_get_encoder_mode (int /*<<< orphan*/ ) ; 
 int radeon_get_pll_use_mask (struct drm_crtc*) ; 
 int radeon_get_shared_dp_ppll (struct drm_crtc*) ; 
 int radeon_get_shared_nondp_ppll (struct drm_crtc*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_encoder* to_radeon_encoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_atom_pick_pll(struct drm_crtc *crtc)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	u32 pll_in_use;
	int pll;

	if (ASIC_IS_DCE8(rdev)) {
		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) {
			if (rdev->clock.dp_extclk)
				/* skip PPLL programming if using ext clock */
				return ATOM_PPLL_INVALID;
			else {
				/* use the same PPLL for all DP monitors */
				pll = radeon_get_shared_dp_ppll(crtc);
				if (pll != ATOM_PPLL_INVALID)
					return pll;
			}
		} else {
			/* use the same PPLL for all monitors with the same clock */
			pll = radeon_get_shared_nondp_ppll(crtc);
			if (pll != ATOM_PPLL_INVALID)
				return pll;
		}
		/* otherwise, pick one of the plls */
		if ((rdev->family == CHIP_KABINI) ||
		    (rdev->family == CHIP_MULLINS)) {
			/* KB/ML has PPLL1 and PPLL2 */
			pll_in_use = radeon_get_pll_use_mask(crtc);
			if (!(pll_in_use & (1 << ATOM_PPLL2)))
				return ATOM_PPLL2;
			if (!(pll_in_use & (1 << ATOM_PPLL1)))
				return ATOM_PPLL1;
			DRM_ERROR("unable to allocate a PPLL\n");
			return ATOM_PPLL_INVALID;
		} else {
			/* CI/KV has PPLL0, PPLL1, and PPLL2 */
			pll_in_use = radeon_get_pll_use_mask(crtc);
			if (!(pll_in_use & (1 << ATOM_PPLL2)))
				return ATOM_PPLL2;
			if (!(pll_in_use & (1 << ATOM_PPLL1)))
				return ATOM_PPLL1;
			if (!(pll_in_use & (1 << ATOM_PPLL0)))
				return ATOM_PPLL0;
			DRM_ERROR("unable to allocate a PPLL\n");
			return ATOM_PPLL_INVALID;
		}
	} else if (ASIC_IS_DCE61(rdev)) {
		struct radeon_encoder_atom_dig *dig =
			radeon_encoder->enc_priv;

		if ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_UNIPHY) &&
		    (dig->linkb == false))
			/* UNIPHY A uses PPLL2 */
			return ATOM_PPLL2;
		else if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) {
			/* UNIPHY B/C/D/E/F */
			if (rdev->clock.dp_extclk)
				/* skip PPLL programming if using ext clock */
				return ATOM_PPLL_INVALID;
			else {
				/* use the same PPLL for all DP monitors */
				pll = radeon_get_shared_dp_ppll(crtc);
				if (pll != ATOM_PPLL_INVALID)
					return pll;
			}
		} else {
			/* use the same PPLL for all monitors with the same clock */
			pll = radeon_get_shared_nondp_ppll(crtc);
			if (pll != ATOM_PPLL_INVALID)
				return pll;
		}
		/* UNIPHY B/C/D/E/F */
		pll_in_use = radeon_get_pll_use_mask(crtc);
		if (!(pll_in_use & (1 << ATOM_PPLL0)))
			return ATOM_PPLL0;
		if (!(pll_in_use & (1 << ATOM_PPLL1)))
			return ATOM_PPLL1;
		DRM_ERROR("unable to allocate a PPLL\n");
		return ATOM_PPLL_INVALID;
	} else if (ASIC_IS_DCE41(rdev)) {
		/* Don't share PLLs on DCE4.1 chips */
		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) {
			if (rdev->clock.dp_extclk)
				/* skip PPLL programming if using ext clock */
				return ATOM_PPLL_INVALID;
		}
		pll_in_use = radeon_get_pll_use_mask(crtc);
		if (!(pll_in_use & (1 << ATOM_PPLL1)))
			return ATOM_PPLL1;
		if (!(pll_in_use & (1 << ATOM_PPLL2)))
			return ATOM_PPLL2;
		DRM_ERROR("unable to allocate a PPLL\n");
		return ATOM_PPLL_INVALID;
	} else if (ASIC_IS_DCE4(rdev)) {
		/* in DP mode, the DP ref clock can come from PPLL, DCPLL, or ext clock,
		 * depending on the asic:
		 * DCE4: PPLL or ext clock
		 * DCE5: PPLL, DCPLL, or ext clock
		 * DCE6: PPLL, PPLL0, or ext clock
		 *
		 * Setting ATOM_PPLL_INVALID will cause SetPixelClock to skip
		 * PPLL/DCPLL programming and only program the DP DTO for the
		 * crtc virtual pixel clock.
		 */
		if (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) {
			if (rdev->clock.dp_extclk)
				/* skip PPLL programming if using ext clock */
				return ATOM_PPLL_INVALID;
			else if (ASIC_IS_DCE6(rdev))
				/* use PPLL0 for all DP */
				return ATOM_PPLL0;
			else if (ASIC_IS_DCE5(rdev))
				/* use DCPLL for all DP */
				return ATOM_DCPLL;
			else {
				/* use the same PPLL for all DP monitors */
				pll = radeon_get_shared_dp_ppll(crtc);
				if (pll != ATOM_PPLL_INVALID)
					return pll;
			}
		} else {
			/* use the same PPLL for all monitors with the same clock */
			pll = radeon_get_shared_nondp_ppll(crtc);
			if (pll != ATOM_PPLL_INVALID)
				return pll;
		}
		/* all other cases */
		pll_in_use = radeon_get_pll_use_mask(crtc);
		if (!(pll_in_use & (1 << ATOM_PPLL1)))
			return ATOM_PPLL1;
		if (!(pll_in_use & (1 << ATOM_PPLL2)))
			return ATOM_PPLL2;
		DRM_ERROR("unable to allocate a PPLL\n");
		return ATOM_PPLL_INVALID;
	} else {
		/* on pre-R5xx asics, the crtc to pll mapping is hardcoded */
		/* some atombios (observed in some DCE2/DCE3) code have a bug,
		 * the matching btw pll and crtc is done through
		 * PCLK_CRTC[1|2]_CNTL (0x480/0x484) but atombios code use the
		 * pll (1 or 2) to select which register to write. ie if using
		 * pll1 it will use PCLK_CRTC1_CNTL (0x480) and if using pll2
		 * it will use PCLK_CRTC2_CNTL (0x484), it then use crtc id to
		 * choose which value to write. Which is reverse order from
		 * register logic. So only case that works is when pllid is
		 * same as crtcid or when both pll and crtc are enabled and
		 * both use same clock.
		 *
		 * So just return crtc id as if crtc and pll were hard linked
		 * together even if they aren't
		 */
		return radeon_crtc->crtc_id;
	}
}