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
struct drm_display_mode {int dummy; } ;
struct dpu_encoder_phys {struct drm_display_mode cached_mode; int /*<<< orphan*/  dpu_kms; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_VIDENC (struct dpu_encoder_phys*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  _dpu_encoder_phys_vid_setup_irq_hw_idx (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 

__attribute__((used)) static void dpu_encoder_phys_vid_mode_set(
		struct dpu_encoder_phys *phys_enc,
		struct drm_display_mode *mode,
		struct drm_display_mode *adj_mode)
{
	if (!phys_enc || !phys_enc->dpu_kms) {
		DPU_ERROR("invalid encoder/kms\n");
		return;
	}

	if (adj_mode) {
		phys_enc->cached_mode = *adj_mode;
		drm_mode_debug_printmodeline(adj_mode);
		DPU_DEBUG_VIDENC(phys_enc, "caching mode:\n");
	}

	_dpu_encoder_phys_vid_setup_irq_hw_idx(phys_enc);
}