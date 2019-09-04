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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; } ;
struct drm_crtc {int dummy; } ;
struct dpu_rm_hw_iter {scalar_t__ hw; } ;
struct dpu_rm {int dummy; } ;
struct dpu_kms {struct dpu_rm rm; } ;
struct dpu_hw_mixer {scalar_t__ idx; } ;
struct dpu_hw_ctl {scalar_t__ idx; } ;
struct dpu_crtc_mixer {struct dpu_hw_ctl* hw_ctl; struct dpu_hw_mixer* hw_lm; struct drm_encoder* encoder; } ;
struct dpu_crtc {int num_mixers; struct dpu_crtc_mixer* mixers; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpu_crtc_mixer*) ; 
 scalar_t__ CTL_0 ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  DPU_HW_BLK_CTL ; 
 int /*<<< orphan*/  DPU_HW_BLK_LM ; 
 scalar_t__ LM_0 ; 
 struct dpu_kms* _dpu_crtc_get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  dpu_rm_get_hw (struct dpu_rm*,struct dpu_rm_hw_iter*) ; 
 int /*<<< orphan*/  dpu_rm_init_hw_iter (struct dpu_rm_hw_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void _dpu_crtc_setup_mixer_for_encoder(
		struct drm_crtc *crtc,
		struct drm_encoder *enc)
{
	struct dpu_crtc *dpu_crtc = to_dpu_crtc(crtc);
	struct dpu_kms *dpu_kms = _dpu_crtc_get_kms(crtc);
	struct dpu_rm *rm = &dpu_kms->rm;
	struct dpu_crtc_mixer *mixer;
	struct dpu_hw_ctl *last_valid_ctl = NULL;
	int i;
	struct dpu_rm_hw_iter lm_iter, ctl_iter;

	dpu_rm_init_hw_iter(&lm_iter, enc->base.id, DPU_HW_BLK_LM);
	dpu_rm_init_hw_iter(&ctl_iter, enc->base.id, DPU_HW_BLK_CTL);

	/* Set up all the mixers and ctls reserved by this encoder */
	for (i = dpu_crtc->num_mixers; i < ARRAY_SIZE(dpu_crtc->mixers); i++) {
		mixer = &dpu_crtc->mixers[i];

		if (!dpu_rm_get_hw(rm, &lm_iter))
			break;
		mixer->hw_lm = (struct dpu_hw_mixer *)lm_iter.hw;

		/* CTL may be <= LMs, if <, multiple LMs controlled by 1 CTL */
		if (!dpu_rm_get_hw(rm, &ctl_iter)) {
			DPU_DEBUG("no ctl assigned to lm %d, using previous\n",
					mixer->hw_lm->idx - LM_0);
			mixer->hw_ctl = last_valid_ctl;
		} else {
			mixer->hw_ctl = (struct dpu_hw_ctl *)ctl_iter.hw;
			last_valid_ctl = mixer->hw_ctl;
		}

		/* Shouldn't happen, mixers are always >= ctls */
		if (!mixer->hw_ctl) {
			DPU_ERROR("no valid ctls found for lm %d\n",
					mixer->hw_lm->idx - LM_0);
			return;
		}

		mixer->encoder = enc;

		dpu_crtc->num_mixers++;
		DPU_DEBUG("setup mixer %d: lm %d\n",
				i, mixer->hw_lm->idx - LM_0);
		DPU_DEBUG("setup mixer %d: ctl %d\n",
				i, mixer->hw_ctl->idx - CTL_0);
	}
}