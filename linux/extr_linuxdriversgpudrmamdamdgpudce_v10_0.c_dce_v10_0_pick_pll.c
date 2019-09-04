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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {scalar_t__ dp_extclk; } ;
struct amdgpu_device {TYPE_1__ clock; } ;
struct amdgpu_crtc {int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int ATOM_PPLL0 ; 
 int ATOM_PPLL1 ; 
 int ATOM_PPLL2 ; 
 int ATOM_PPLL_INVALID ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ ENCODER_MODE_IS_DP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_get_encoder_mode (int /*<<< orphan*/ ) ; 
 int amdgpu_pll_get_shared_dp_ppll (struct drm_crtc*) ; 
 int amdgpu_pll_get_shared_nondp_ppll (struct drm_crtc*) ; 
 int amdgpu_pll_get_use_mask (struct drm_crtc*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static u32 dce_v10_0_pick_pll(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	u32 pll_in_use;
	int pll;

	if (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder))) {
		if (adev->clock.dp_extclk)
			/* skip PPLL programming if using ext clock */
			return ATOM_PPLL_INVALID;
		else {
			/* use the same PPLL for all DP monitors */
			pll = amdgpu_pll_get_shared_dp_ppll(crtc);
			if (pll != ATOM_PPLL_INVALID)
				return pll;
		}
	} else {
		/* use the same PPLL for all monitors with the same clock */
		pll = amdgpu_pll_get_shared_nondp_ppll(crtc);
		if (pll != ATOM_PPLL_INVALID)
			return pll;
	}

	/* DCE10 has PPLL0, PPLL1, and PPLL2 */
	pll_in_use = amdgpu_pll_get_use_mask(crtc);
	if (!(pll_in_use & (1 << ATOM_PPLL2)))
		return ATOM_PPLL2;
	if (!(pll_in_use & (1 << ATOM_PPLL1)))
		return ATOM_PPLL1;
	if (!(pll_in_use & (1 << ATOM_PPLL0)))
		return ATOM_PPLL0;
	DRM_ERROR("unable to allocate a PPLL\n");
	return ATOM_PPLL_INVALID;
}