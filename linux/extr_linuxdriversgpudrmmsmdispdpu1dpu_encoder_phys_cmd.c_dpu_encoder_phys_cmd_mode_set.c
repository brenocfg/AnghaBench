#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_display_mode {int dummy; } ;
struct dpu_rm_hw_iter {scalar_t__ hw; } ;
struct dpu_rm {int dummy; } ;
struct dpu_hw_ctl {int dummy; } ;
struct dpu_encoder_phys_cmd {int dummy; } ;
struct dpu_encoder_phys {scalar_t__ split_role; struct dpu_hw_ctl* hw_ctl; TYPE_3__* parent; struct drm_display_mode cached_mode; TYPE_1__* dpu_kms; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct TYPE_4__ {struct dpu_rm rm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_CMDENC (struct dpu_encoder_phys_cmd*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_CMDENC (struct dpu_encoder_phys_cmd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_HW_BLK_CTL ; 
 scalar_t__ ENC_ROLE_SLAVE ; 
 scalar_t__ IS_ERR_OR_NULL (struct dpu_hw_ctl*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dpu_hw_ctl*) ; 
 int /*<<< orphan*/  _dpu_encoder_phys_cmd_setup_irq_hw_idx (struct dpu_encoder_phys*) ; 
 scalar_t__ dpu_rm_get_hw (struct dpu_rm*,struct dpu_rm_hw_iter*) ; 
 int /*<<< orphan*/  dpu_rm_init_hw_iter (struct dpu_rm_hw_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_mode_set(
		struct dpu_encoder_phys *phys_enc,
		struct drm_display_mode *mode,
		struct drm_display_mode *adj_mode)
{
	struct dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);
	struct dpu_rm *rm = &phys_enc->dpu_kms->rm;
	struct dpu_rm_hw_iter iter;
	int i, instance;

	if (!phys_enc || !mode || !adj_mode) {
		DPU_ERROR("invalid args\n");
		return;
	}
	phys_enc->cached_mode = *adj_mode;
	DPU_DEBUG_CMDENC(cmd_enc, "caching mode:\n");
	drm_mode_debug_printmodeline(adj_mode);

	instance = phys_enc->split_role == ENC_ROLE_SLAVE ? 1 : 0;

	/* Retrieve previously allocated HW Resources. Shouldn't fail */
	dpu_rm_init_hw_iter(&iter, phys_enc->parent->base.id, DPU_HW_BLK_CTL);
	for (i = 0; i <= instance; i++) {
		if (dpu_rm_get_hw(rm, &iter))
			phys_enc->hw_ctl = (struct dpu_hw_ctl *)iter.hw;
	}

	if (IS_ERR_OR_NULL(phys_enc->hw_ctl)) {
		DPU_ERROR_CMDENC(cmd_enc, "failed to init ctl: %ld\n",
				PTR_ERR(phys_enc->hw_ctl));
		phys_enc->hw_ctl = NULL;
		return;
	}

	_dpu_encoder_phys_cmd_setup_irq_hw_idx(phys_enc);
}