#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_display_mode {int clock; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct amdgpu_pll {int reference_freq; int /*<<< orphan*/  post_div; int /*<<< orphan*/  reference_div; int /*<<< orphan*/  flags; } ;
struct amdgpu_encoder {int /*<<< orphan*/  encoder_id; } ;
struct TYPE_4__ {struct amdgpu_pll* ppll; } ;
struct amdgpu_device {TYPE_1__ clock; } ;
struct TYPE_5__ {int amount; int type; int step; scalar_t__ rate; scalar_t__ percentage_divider; scalar_t__ percentage; } ;
struct amdgpu_crtc {int bpc; int adjusted_clock; int pll_id; TYPE_2__ ss; int /*<<< orphan*/  crtc_id; scalar_t__ ss_enabled; int /*<<< orphan*/  pll_post_div; int /*<<< orphan*/  pll_reference_div; int /*<<< orphan*/  pll_flags; int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int ATOM_ENCODER_MODE_HDMI ; 
#define  ATOM_PPLL0 131 
#define  ATOM_PPLL1 130 
#define  ATOM_PPLL2 129 
#define  ATOM_PPLL_INVALID 128 
 int ATOM_PPLL_SS_AMOUNT_V2_FBDIV_MASK ; 
 int ATOM_PPLL_SS_AMOUNT_V2_NFRAC_MASK ; 
 int ATOM_PPLL_SS_AMOUNT_V2_NFRAC_SHIFT ; 
 int ATOM_PPLL_SS_TYPE_V2_CENTRE_SPREAD ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_program_pll (struct drm_crtc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_program_ss (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int amdgpu_atombios_encoder_get_encoder_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_pll_compute (struct amdgpu_pll*,int,int*,int*,int*,int*,int*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (int /*<<< orphan*/ ) ; 

void amdgpu_atombios_crtc_set_pll(struct drm_crtc *crtc, struct drm_display_mode *mode)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder =
		to_amdgpu_encoder(amdgpu_crtc->encoder);
	u32 pll_clock = mode->clock;
	u32 clock = mode->clock;
	u32 ref_div = 0, fb_div = 0, frac_fb_div = 0, post_div = 0;
	struct amdgpu_pll *pll;
	int encoder_mode = amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder);

	/* pass the actual clock to amdgpu_atombios_crtc_program_pll for HDMI */
	if ((encoder_mode == ATOM_ENCODER_MODE_HDMI) &&
	    (amdgpu_crtc->bpc > 8))
		clock = amdgpu_crtc->adjusted_clock;

	switch (amdgpu_crtc->pll_id) {
	case ATOM_PPLL1:
		pll = &adev->clock.ppll[0];
		break;
	case ATOM_PPLL2:
		pll = &adev->clock.ppll[1];
		break;
	case ATOM_PPLL0:
	case ATOM_PPLL_INVALID:
	default:
		pll = &adev->clock.ppll[2];
		break;
	}

	/* update pll params */
	pll->flags = amdgpu_crtc->pll_flags;
	pll->reference_div = amdgpu_crtc->pll_reference_div;
	pll->post_div = amdgpu_crtc->pll_post_div;

	amdgpu_pll_compute(pll, amdgpu_crtc->adjusted_clock, &pll_clock,
			    &fb_div, &frac_fb_div, &ref_div, &post_div);

	amdgpu_atombios_crtc_program_ss(adev, ATOM_DISABLE, amdgpu_crtc->pll_id,
				 amdgpu_crtc->crtc_id, &amdgpu_crtc->ss);

	amdgpu_atombios_crtc_program_pll(crtc, amdgpu_crtc->crtc_id, amdgpu_crtc->pll_id,
				  encoder_mode, amdgpu_encoder->encoder_id, clock,
				  ref_div, fb_div, frac_fb_div, post_div,
				  amdgpu_crtc->bpc, amdgpu_crtc->ss_enabled, &amdgpu_crtc->ss);

	if (amdgpu_crtc->ss_enabled) {
		/* calculate ss amount and step size */
		u32 step_size;
		u32 amount = (((fb_div * 10) + frac_fb_div) *
			      (u32)amdgpu_crtc->ss.percentage) /
			(100 * (u32)amdgpu_crtc->ss.percentage_divider);
		amdgpu_crtc->ss.amount = (amount / 10) & ATOM_PPLL_SS_AMOUNT_V2_FBDIV_MASK;
		amdgpu_crtc->ss.amount |= ((amount - (amount / 10)) << ATOM_PPLL_SS_AMOUNT_V2_NFRAC_SHIFT) &
			ATOM_PPLL_SS_AMOUNT_V2_NFRAC_MASK;
		if (amdgpu_crtc->ss.type & ATOM_PPLL_SS_TYPE_V2_CENTRE_SPREAD)
			step_size = (4 * amount * ref_div * ((u32)amdgpu_crtc->ss.rate * 2048)) /
				(125 * 25 * pll->reference_freq / 100);
		else
			step_size = (2 * amount * ref_div * ((u32)amdgpu_crtc->ss.rate * 2048)) /
				(125 * 25 * pll->reference_freq / 100);
		amdgpu_crtc->ss.step = step_size;

		amdgpu_atombios_crtc_program_ss(adev, ATOM_ENABLE, amdgpu_crtc->pll_id,
					 amdgpu_crtc->crtc_id, &amdgpu_crtc->ss);
	}
}