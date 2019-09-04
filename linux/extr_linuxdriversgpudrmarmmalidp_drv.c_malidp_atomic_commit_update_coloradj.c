#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct malidp_hw_device {TYPE_6__* hw; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct malidp_crtc_state {int /*<<< orphan*/ * coloradj_coeffs; } ;
struct drm_crtc_state {TYPE_4__* ctm; } ;
struct drm_crtc {TYPE_7__* state; } ;
struct TYPE_14__ {TYPE_2__* ctm; int /*<<< orphan*/  color_mgmt_changed; } ;
struct TYPE_12__ {scalar_t__ coeffs_base; } ;
struct TYPE_13__ {TYPE_5__ map; } ;
struct TYPE_10__ {scalar_t__ id; } ;
struct TYPE_11__ {TYPE_3__ base; } ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_9__ {TYPE_1__ base; } ;

/* Variables and functions */
 int MALIDP_COLORADJ_NUM_COEFFS ; 
 scalar_t__ MALIDP_COLOR_ADJ_COEF ; 
 int /*<<< orphan*/  MALIDP_DE_DISPLAY_FUNC ; 
 int /*<<< orphan*/  MALIDP_DISP_FUNC_CADJ ; 
 struct malidp_drm* crtc_to_malidp_device (struct drm_crtc*) ; 
 int /*<<< orphan*/  malidp_hw_clearbits (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_setbits (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct malidp_crtc_state* to_malidp_crtc_state (TYPE_7__*) ; 

__attribute__((used)) static
void malidp_atomic_commit_update_coloradj(struct drm_crtc *crtc,
					  struct drm_crtc_state *old_state)
{
	struct malidp_drm *malidp = crtc_to_malidp_device(crtc);
	struct malidp_hw_device *hwdev = malidp->dev;
	int i;

	if (!crtc->state->color_mgmt_changed)
		return;

	if (!crtc->state->ctm) {
		malidp_hw_clearbits(hwdev, MALIDP_DISP_FUNC_CADJ,
				    MALIDP_DE_DISPLAY_FUNC);
	} else {
		struct malidp_crtc_state *mc =
			to_malidp_crtc_state(crtc->state);

		if (!old_state->ctm || (crtc->state->ctm->base.id !=
					old_state->ctm->base.id))
			for (i = 0; i < MALIDP_COLORADJ_NUM_COEFFS; ++i)
				malidp_hw_write(hwdev,
						mc->coloradj_coeffs[i],
						hwdev->hw->map.coeffs_base +
						MALIDP_COLOR_ADJ_COEF + 4 * i);

		malidp_hw_setbits(hwdev, MALIDP_DISP_FUNC_CADJ,
				  MALIDP_DE_DISPLAY_FUNC);
	}
}