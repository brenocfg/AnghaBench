#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_crtc {TYPE_2__* primary; struct drm_device* dev; } ;
struct TYPE_8__ {int num_crtc; TYPE_3__** crtcs; } ;
struct amdgpu_device {TYPE_4__ mode_info; } ;
struct amdgpu_crtc {int crtc_id; int pll_id; int /*<<< orphan*/ * connector; int /*<<< orphan*/ * encoder; scalar_t__ adjusted_clock; } ;
struct amdgpu_bo {int dummy; } ;
struct amdgpu_atom_ss {int dummy; } ;
struct TYPE_7__ {int pll_id; scalar_t__ enabled; } ;
struct TYPE_6__ {TYPE_1__* fb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
#define  ATOM_COMBOPHY_PLL0 136 
#define  ATOM_COMBOPHY_PLL1 135 
#define  ATOM_COMBOPHY_PLL2 134 
#define  ATOM_COMBOPHY_PLL3 133 
#define  ATOM_COMBOPHY_PLL4 132 
#define  ATOM_COMBOPHY_PLL5 131 
 int ATOM_CRTC_INVALID ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
#define  ATOM_PPLL0 130 
#define  ATOM_PPLL1 129 
#define  ATOM_PPLL2 128 
 int ATOM_PPLL_INVALID ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_powergate (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_program_pll (struct drm_crtc*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct amdgpu_atom_ss*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  dce_v11_0_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v11_0_grph_enable (struct drm_crtc*,int) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (int /*<<< orphan*/ ) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dce_v11_0_crtc_disable(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_atom_ss ss;
	int i;

	dce_v11_0_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	if (crtc->primary->fb) {
		int r;
		struct amdgpu_bo *abo;

		abo = gem_to_amdgpu_bo(crtc->primary->fb->obj[0]);
		r = amdgpu_bo_reserve(abo, true);
		if (unlikely(r))
			DRM_ERROR("failed to reserve abo before unpin\n");
		else {
			amdgpu_bo_unpin(abo);
			amdgpu_bo_unreserve(abo);
		}
	}
	/* disable the GRPH */
	dce_v11_0_grph_enable(crtc, false);

	amdgpu_atombios_crtc_powergate(crtc, ATOM_ENABLE);

	for (i = 0; i < adev->mode_info.num_crtc; i++) {
		if (adev->mode_info.crtcs[i] &&
		    adev->mode_info.crtcs[i]->enabled &&
		    i != amdgpu_crtc->crtc_id &&
		    amdgpu_crtc->pll_id == adev->mode_info.crtcs[i]->pll_id) {
			/* one other crtc is using this pll don't turn
			 * off the pll
			 */
			goto done;
		}
	}

	switch (amdgpu_crtc->pll_id) {
	case ATOM_PPLL0:
	case ATOM_PPLL1:
	case ATOM_PPLL2:
		/* disable the ppll */
		amdgpu_atombios_crtc_program_pll(crtc, amdgpu_crtc->crtc_id, amdgpu_crtc->pll_id,
						 0, 0, ATOM_DISABLE, 0, 0, 0, 0, 0, false, &ss);
		break;
	case ATOM_COMBOPHY_PLL0:
	case ATOM_COMBOPHY_PLL1:
	case ATOM_COMBOPHY_PLL2:
	case ATOM_COMBOPHY_PLL3:
	case ATOM_COMBOPHY_PLL4:
	case ATOM_COMBOPHY_PLL5:
		/* disable the ppll */
		amdgpu_atombios_crtc_program_pll(crtc, ATOM_CRTC_INVALID, amdgpu_crtc->pll_id,
						 0, 0, ATOM_DISABLE, 0, 0, 0, 0, 0, false, &ss);
		break;
	default:
		break;
	}
done:
	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->adjusted_clock = 0;
	amdgpu_crtc->encoder = NULL;
	amdgpu_crtc->connector = NULL;
}